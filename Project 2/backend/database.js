const sqlite3 = require('sqlite3').verbose();
const path = require('path');

const dbPath = path.join(__dirname, 'hajj_management.db');
const db = new sqlite3.Database(dbPath);

db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS pilgrims (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        age INTEGER NOT NULL,
        gender TEXT NOT NULL,
        country TEXT NOT NULL,
        phone TEXT,
        email TEXT,
        passport_number TEXT UNIQUE,
        is_elderly BOOLEAN DEFAULT 0,
        is_disabled BOOLEAN DEFAULT 0,
        group_number INTEGER,
        accommodation_id INTEGER,
        registration_date DATETIME DEFAULT CURRENT_TIMESTAMP,
        hajj_status TEXT DEFAULT 'Registered',
        FOREIGN KEY (accommodation_id) REFERENCES accommodations(id)
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS payments (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        pilgrim_id INTEGER NOT NULL,
        total_amount DECIMAL(10, 2) NOT NULL,
        paid_amount DECIMAL(10, 2) DEFAULT 0,
        remaining_amount DECIMAL(10, 2),
        payment_status TEXT DEFAULT 'Pending',
        payment_method TEXT,
        transaction_id TEXT,
        payment_date DATETIME,
        due_date DATE,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (pilgrim_id) REFERENCES pilgrims(id) ON DELETE CASCADE
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS payment_installments (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        payment_id INTEGER NOT NULL,
        installment_number INTEGER NOT NULL,
        amount DECIMAL(10, 2) NOT NULL,
        payment_date DATETIME,
        status TEXT DEFAULT 'Pending',
        transaction_reference TEXT,
        FOREIGN KEY (payment_id) REFERENCES payments(id) ON DELETE CASCADE
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS accommodations (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        location TEXT NOT NULL,
        capacity INTEGER NOT NULL,
        occupied INTEGER DEFAULT 0,
        price_per_person DECIMAL(10, 2) DEFAULT 0,
        amenities TEXT,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS transportation_queue (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        pilgrim_id INTEGER NOT NULL,
        queue_position INTEGER,
        priority_level INTEGER DEFAULT 3,
        destination TEXT,
        departure_time DATETIME,
        status TEXT DEFAULT 'Waiting',
        added_at DATETIME DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (pilgrim_id) REFERENCES pilgrims(id) ON DELETE CASCADE
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS rituals (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        pilgrim_id INTEGER NOT NULL,
        ritual_name TEXT NOT NULL,
        ritual_status TEXT DEFAULT 'Pending',
        completed_at DATETIME,
        location TEXT,
        notes TEXT,
        FOREIGN KEY (pilgrim_id) REFERENCES pilgrims(id) ON DELETE CASCADE
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT UNIQUE NOT NULL,
        password TEXT NOT NULL,
        full_name TEXT,
        role TEXT DEFAULT 'admin',
        email TEXT,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);

    db.run(`INSERT OR IGNORE INTO accommodations (id, location, capacity, price_per_person, amenities) VALUES
        (1, 'Makkah - Hotel Al-Safa', 150, 2500.00, 'AC, WiFi, Meals'),
        (2, 'Makkah - Hotel Dar Al-Tawhid', 200, 3000.00, 'AC, WiFi, Meals, Transport'),
        (3, 'Mina - Tent Camp A', 300, 1500.00, 'Basic Amenities'),
        (4, 'Mina - Tent Camp B', 300, 1500.00, 'Basic Amenities'),
        (5, 'Arafat - Tent Camp', 500, 1000.00, 'Basic Amenities'),
        (6, 'Muzdalifah - Open Area', 400, 800.00, 'Open Space')
    `);

    const bcrypt = require('bcrypt');
    const defaultPassword = 'admin123';
    bcrypt.hash(defaultPassword, 10, (err, hash) => {
        if (!err) {
            db.run(`INSERT OR IGNORE INTO users (id, username, password, full_name, role, email) VALUES
                (1, 'admin', ?, 'System Administrator', 'admin', 'admin@hajj.com')
            `, [hash]);
        }
    });
});

module.exports = db;
