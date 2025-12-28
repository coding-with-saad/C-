const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const db = require('./database');
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');

const app = express();
const PORT = 3000;
const SECRET_KEY = 'hajj_secret_key_2025';

app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

const authenticateToken = (req, res, next) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    if (!token) return res.status(401).json({ error: 'Access denied' });

    jwt.verify(token, SECRET_KEY, (err, user) => {
        if (err) return res.status(403).json({ error: 'Invalid token' });
        req.user = user;
        next();
    });
};

app.post('/api/login', (req, res) => {
    const { username, password } = req.body;

    db.get('SELECT * FROM users WHERE username = ?', [username], (err, user) => {
        if (err) return res.status(500).json({ error: err.message });
        if (!user) return res.status(401).json({ error: 'Invalid credentials' });

        bcrypt.compare(password, user.password, (err, result) => {
            if (result) {
                const token = jwt.sign({ id: user.id, username: user.username }, SECRET_KEY, { expiresIn: '24h' });
                res.json({ token, user: { id: user.id, username: user.username, fullName: user.full_name, role: user.role } });
            } else {
                res.status(401).json({ error: 'Invalid credentials' });
            }
        });
    });
});

app.get('/api/pilgrims', authenticateToken, (req, res) => {
    const query = `
        SELECT p.*, a.location as accommodation_name,
               pay.payment_status, pay.paid_amount, pay.total_amount, pay.remaining_amount
        FROM pilgrims p
        LEFT JOIN accommodations a ON p.accommodation_id = a.id
        LEFT JOIN payments pay ON p.id = pay.pilgrim_id
        ORDER BY p.id DESC
    `;

    db.all(query, [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

app.get('/api/pilgrims/:id', authenticateToken, (req, res) => {
    const query = `
        SELECT p.*, a.location as accommodation_name, a.price_per_person,
               pay.payment_status, pay.paid_amount, pay.total_amount, pay.remaining_amount,
               pay.payment_method, pay.payment_date
        FROM pilgrims p
        LEFT JOIN accommodations a ON p.accommodation_id = a.id
        LEFT JOIN payments pay ON p.id = pay.pilgrim_id
        WHERE p.id = ?
    `;

    db.get(query, [req.params.id], (err, row) => {
        if (err) return res.status(500).json({ error: err.message });
        if (!row) return res.status(404).json({ error: 'Pilgrim not found' });
        res.json(row);
    });
});

app.post('/api/pilgrims', authenticateToken, (req, res) => {
    const { name, age, gender, country, phone, email, passport_number, is_elderly, is_disabled, group_number } = req.body;

    db.get('SELECT id FROM accommodations WHERE occupied < capacity ORDER BY id LIMIT 1', [], (err, accommodation) => {
        const accommodation_id = accommodation ? accommodation.id : null;

        const query = `INSERT INTO pilgrims (name, age, gender, country, phone, email, passport_number, is_elderly, is_disabled, group_number, accommodation_id, hajj_status)
                       VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 'Registered')`;

        db.run(query, [name, age, gender, country, phone, email, passport_number, is_elderly ? 1 : 0, is_disabled ? 1 : 0, group_number, accommodation_id], function(err) {
            if (err) return res.status(500).json({ error: err.message });

            if (accommodation_id) {
                db.run('UPDATE accommodations SET occupied = occupied + 1 WHERE id = ?', [accommodation_id]);
            }

            db.get('SELECT price_per_person FROM accommodations WHERE id = ?', [accommodation_id], (err, accom) => {
                const basePrice = accom ? accom.price_per_person : 5000;
                const totalAmount = basePrice + 3000;

                db.run('INSERT INTO payments (pilgrim_id, total_amount, remaining_amount, payment_status) VALUES (?, ?, ?, ?)',
                    [this.lastID, totalAmount, totalAmount, 'Pending']);
            });

            const rituals = [
                'Ihram (State of Consecration)',
                'Tawaf (Circumambulation of Kaaba)',
                'Sa\'i (Walking between Safa and Marwa)',
                'Standing at Arafat',
                'Muzdalifah (Night Stay)',
                'Rami (Stoning the Devil)',
                'Sacrifice (Qurbani)'
            ];

            const stmt = db.prepare('INSERT INTO rituals (pilgrim_id, ritual_name) VALUES (?, ?)');
            rituals.forEach(ritual => stmt.run(this.lastID, ritual));
            stmt.finalize();

            res.json({ id: this.lastID, message: 'Pilgrim registered successfully', accommodation_id });
        });
    });
});

app.put('/api/pilgrims/:id', authenticateToken, (req, res) => {
    const { name, age, gender, country, phone, email, is_elderly, is_disabled, group_number, hajj_status } = req.body;

    const query = `UPDATE pilgrims SET name = ?, age = ?, gender = ?, country = ?, phone = ?, email = ?,
                   is_elderly = ?, is_disabled = ?, group_number = ?, hajj_status = ? WHERE id = ?`;

    db.run(query, [name, age, gender, country, phone, email, is_elderly ? 1 : 0, is_disabled ? 1 : 0, group_number, hajj_status, req.params.id], function(err) {
        if (err) return res.status(500).json({ error: err.message });
        res.json({ message: 'Pilgrim updated successfully', changes: this.changes });
    });
});

app.delete('/api/pilgrims/:id', authenticateToken, (req, res) => {
    db.get('SELECT accommodation_id FROM pilgrims WHERE id = ?', [req.params.id], (err, pilgrim) => {
        if (pilgrim && pilgrim.accommodation_id) {
            db.run('UPDATE accommodations SET occupied = occupied - 1 WHERE id = ?', [pilgrim.accommodation_id]);
        }

        db.run('DELETE FROM pilgrims WHERE id = ?', [req.params.id], function(err) {
            if (err) return res.status(500).json({ error: err.message });
            res.json({ message: 'Pilgrim deleted successfully', changes: this.changes });
        });
    });
});

app.get('/api/accommodations', authenticateToken, (req, res) => {
    db.all('SELECT * FROM accommodations ORDER BY id', [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

app.get('/api/payments', authenticateToken, (req, res) => {
    const query = `
        SELECT pay.*, p.name as pilgrim_name, p.passport_number
        FROM payments pay
        JOIN pilgrims p ON pay.pilgrim_id = p.id
        ORDER BY pay.id DESC
    `;

    db.all(query, [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

app.get('/api/payments/pilgrim/:pilgrim_id', authenticateToken, (req, res) => {
    db.get('SELECT * FROM payments WHERE pilgrim_id = ?', [req.params.pilgrim_id], (err, row) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(row || {});
    });
});

app.post('/api/payments', authenticateToken, (req, res) => {
    const { pilgrim_id, amount, payment_method, transaction_id } = req.body;

    db.get('SELECT * FROM payments WHERE pilgrim_id = ?', [pilgrim_id], (err, payment) => {
        if (payment) {
            const newPaidAmount = parseFloat(payment.paid_amount) + parseFloat(amount);
            const newRemainingAmount = parseFloat(payment.total_amount) - newPaidAmount;
            const newStatus = newRemainingAmount <= 0 ? 'Paid' : newPaidAmount > 0 ? 'Partial' : 'Pending';

            db.run(`UPDATE payments SET paid_amount = ?, remaining_amount = ?, payment_status = ?,
                    payment_method = ?, payment_date = CURRENT_TIMESTAMP WHERE pilgrim_id = ?`,
                [newPaidAmount, newRemainingAmount, newStatus, payment_method, pilgrim_id], function(err) {
                if (err) return res.status(500).json({ error: err.message });

                db.run(`INSERT INTO payment_installments (payment_id, installment_number, amount, payment_date, status, transaction_reference)
                        SELECT id, (SELECT COUNT(*) FROM payment_installments WHERE payment_id = ?), ?, CURRENT_TIMESTAMP, 'Completed', ?
                        FROM payments WHERE pilgrim_id = ?`,
                    [payment.id, amount, transaction_id, pilgrim_id]);

                res.json({ message: 'Payment updated successfully' });
            });
        } else {
            res.status(404).json({ error: 'Payment record not found' });
        }
    });
});

app.get('/api/transportation-queue', authenticateToken, (req, res) => {
    const query = `
        SELECT tq.*, p.name, p.age, p.is_elderly, p.is_disabled
        FROM transportation_queue tq
        JOIN pilgrims p ON tq.pilgrim_id = p.id
        WHERE tq.status = 'Waiting'
        ORDER BY tq.priority_level, tq.queue_position
    `;

    db.all(query, [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

app.post('/api/transportation-queue', authenticateToken, (req, res) => {
    const { pilgrim_id, destination } = req.body;

    db.get('SELECT is_disabled, is_elderly FROM pilgrims WHERE id = ?', [pilgrim_id], (err, pilgrim) => {
        if (err) return res.status(500).json({ error: err.message });

        const priority = pilgrim.is_disabled ? 1 : pilgrim.is_elderly ? 2 : 3;

        db.run('SELECT MAX(queue_position) as max_pos FROM transportation_queue', [], (err, row) => {
            const position = (row && row.max_pos) ? row.max_pos + 1 : 1;

            db.run('INSERT INTO transportation_queue (pilgrim_id, queue_position, priority_level, destination, status) VALUES (?, ?, ?, ?, ?)',
                [pilgrim_id, position, priority, destination, 'Waiting'], function(err) {
                if (err) return res.status(500).json({ error: err.message });
                res.json({ id: this.lastID, message: 'Added to queue', priority, position });
            });
        });
    });
});

app.put('/api/transportation-queue/:id/board', authenticateToken, (req, res) => {
    db.run('UPDATE transportation_queue SET status = ?, departure_time = CURRENT_TIMESTAMP WHERE id = ?',
        ['Boarded', req.params.id], function(err) {
        if (err) return res.status(500).json({ error: err.message });
        res.json({ message: 'Pilgrim boarded successfully' });
    });
});

app.get('/api/rituals/pilgrim/:pilgrim_id', authenticateToken, (req, res) => {
    db.all('SELECT * FROM rituals WHERE pilgrim_id = ? ORDER BY id', [req.params.pilgrim_id], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

app.put('/api/rituals/:id/complete', authenticateToken, (req, res) => {
    db.run('UPDATE rituals SET ritual_status = ?, completed_at = CURRENT_TIMESTAMP WHERE id = ?',
        ['Completed', req.params.id], function(err) {
        if (err) return res.status(500).json({ error: err.message });
        res.json({ message: 'Ritual marked as completed' });
    });
});

app.get('/api/dashboard/stats', authenticateToken, (req, res) => {
    const stats = {};

    db.get('SELECT COUNT(*) as total FROM pilgrims', [], (err, row) => {
        stats.totalPilgrims = row.total;

        db.get('SELECT COUNT(*) as total FROM pilgrims WHERE hajj_status = "Completed"', [], (err, row) => {
            stats.completedHajj = row.total;

            db.get('SELECT SUM(paid_amount) as total FROM payments', [], (err, row) => {
                stats.totalRevenue = row.total || 0;

                db.get('SELECT SUM(remaining_amount) as total FROM payments WHERE payment_status != "Paid"', [], (err, row) => {
                    stats.pendingPayments = row.total || 0;

                    db.get('SELECT COUNT(*) as total FROM transportation_queue WHERE status = "Waiting"', [], (err, row) => {
                        stats.queueSize = row.total;

                        db.get('SELECT SUM(occupied) as total FROM accommodations', [], (err, row) => {
                            stats.occupiedAccommodations = row.total;

                            db.get('SELECT SUM(capacity) as total FROM accommodations', [], (err, row) => {
                                stats.totalAccommodations = row.total;

                                res.json(stats);
                            });
                        });
                    });
                });
            });
        });
    });
});

app.get('/api/search/pilgrims', authenticateToken, (req, res) => {
    const searchTerm = req.query.q;
    const query = `
        SELECT p.*, a.location as accommodation_name
        FROM pilgrims p
        LEFT JOIN accommodations a ON p.accommodation_id = a.id
        WHERE p.name LIKE ? OR p.passport_number LIKE ? OR p.email LIKE ?
        ORDER BY p.id DESC
    `;

    const searchPattern = `%${searchTerm}%`;
    db.all(query, [searchPattern, searchPattern, searchPattern], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
    console.log('Default login: username=admin, password=admin123');
});
