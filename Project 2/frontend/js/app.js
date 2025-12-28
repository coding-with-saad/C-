const API_URL = 'http://localhost:3000/api';
let authToken = localStorage.getItem('authToken');
let currentUser = JSON.parse(localStorage.getItem('currentUser'));

if (authToken && currentUser) {
    showDashboard();
    loadDashboardData();
}

document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault();

    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;

    try {
        const response = await fetch(`${API_URL}/login`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ username, password })
        });

        const data = await response.json();

        if (response.ok) {
            authToken = data.token;
            currentUser = data.user;
            localStorage.setItem('authToken', authToken);
            localStorage.setItem('currentUser', JSON.stringify(currentUser));
            showDashboard();
            loadDashboardData();
        } else {
            alert(data.error || 'Login failed');
        }
    } catch (error) {
        alert('Connection error. Please ensure the backend server is running.');
        console.error(error);
    }
});

document.getElementById('logoutBtn').addEventListener('click', () => {
    localStorage.removeItem('authToken');
    localStorage.removeItem('currentUser');
    authToken = null;
    currentUser = null;
    location.reload();
});

function showDashboard() {
    document.getElementById('loginPage').style.display = 'none';
    document.getElementById('dashboardPage').style.display = 'flex';
    document.getElementById('currentUser').textContent = `Welcome, ${currentUser.fullName || currentUser.username}`;
}

document.querySelectorAll('.nav-item').forEach(item => {
    item.addEventListener('click', (e) => {
        e.preventDefault();

        document.querySelectorAll('.nav-item').forEach(nav => nav.classList.remove('active'));
        item.classList.add('active');

        const page = item.getAttribute('data-page');

        document.querySelectorAll('.content-section').forEach(section => section.classList.remove('active'));
        document.getElementById(`${page}Content`).classList.add('active');

        if (page === 'dashboard') loadDashboardData();
        else if (page === 'pilgrims') loadPilgrims();
        else if (page === 'payments') loadPayments();
        else if (page === 'transportation') loadTransportationQueue();
        else if (page === 'accommodations') loadAccommodations();
    });
});

async function loadDashboardData() {
    try {
        const response = await fetch(`${API_URL}/dashboard/stats`, {
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        const stats = await response.json();

        document.getElementById('totalPilgrims').textContent = stats.totalPilgrims || 0;
        document.getElementById('completedHajj').textContent = stats.completedHajj || 0;
        document.getElementById('totalRevenue').textContent = `$${(stats.totalRevenue || 0).toFixed(2)}`;
        document.getElementById('pendingPayments').textContent = `$${(stats.pendingPayments || 0).toFixed(2)}`;
        document.getElementById('queueSize').textContent = stats.queueSize || 0;

        const occupancy = stats.totalAccommodations > 0
            ? ((stats.occupiedAccommodations / stats.totalAccommodations) * 100).toFixed(1)
            : 0;

        document.getElementById('occupancyProgress').style.width = `${occupancy}%`;
        document.getElementById('occupancyText').textContent =
            `${stats.occupiedAccommodations || 0} / ${stats.totalAccommodations || 0}`;

    } catch (error) {
        console.error('Error loading dashboard data:', error);
    }
}

async function loadPilgrims() {
    try {
        const response = await fetch(`${API_URL}/pilgrims`, {
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        const pilgrims = await response.json();
        const tbody = document.getElementById('pilgrimsTableBody');
        tbody.innerHTML = '';

        pilgrims.forEach(pilgrim => {
            const statusClass = pilgrim.hajj_status === 'Completed' ? 'success' :
                               pilgrim.hajj_status === 'In Progress' ? 'warning' : 'info';

            const paymentClass = pilgrim.payment_status === 'Paid' ? 'success' :
                                pilgrim.payment_status === 'Partial' ? 'warning' : 'danger';

            const row = `
                <tr>
                    <td>${pilgrim.id}</td>
                    <td>${pilgrim.name}</td>
                    <td>${pilgrim.age}</td>
                    <td>${pilgrim.gender === 'M' ? 'Male' : 'Female'}</td>
                    <td>${pilgrim.country}</td>
                    <td>${pilgrim.passport_number || 'N/A'}</td>
                    <td><span class="badge badge-${statusClass}">${pilgrim.hajj_status}</span></td>
                    <td><span class="badge badge-${paymentClass}">${pilgrim.payment_status || 'Pending'}</span></td>
                    <td>
                        <button class="btn-icon btn-pay" onclick="showPaymentModal(${pilgrim.id})">
                            <i class="fas fa-dollar-sign"></i>
                        </button>
                        <button class="btn-icon btn-delete" onclick="deletePilgrim(${pilgrim.id})">
                            <i class="fas fa-trash"></i>
                        </button>
                    </td>
                </tr>
            `;
            tbody.innerHTML += row;
        });
    } catch (error) {
        console.error('Error loading pilgrims:', error);
    }
}

document.getElementById('searchPilgrims').addEventListener('input', async (e) => {
    const searchTerm = e.target.value;

    if (searchTerm.length < 2) {
        loadPilgrims();
        return;
    }

    try {
        const response = await fetch(`${API_URL}/search/pilgrims?q=${searchTerm}`, {
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        const pilgrims = await response.json();
        const tbody = document.getElementById('pilgrimsTableBody');
        tbody.innerHTML = '';

        pilgrims.forEach(pilgrim => {
            const statusClass = pilgrim.hajj_status === 'Completed' ? 'success' :
                               pilgrim.hajj_status === 'In Progress' ? 'warning' : 'info';

            const row = `
                <tr>
                    <td>${pilgrim.id}</td>
                    <td>${pilgrim.name}</td>
                    <td>${pilgrim.age}</td>
                    <td>${pilgrim.gender === 'M' ? 'Male' : 'Female'}</td>
                    <td>${pilgrim.country}</td>
                    <td>${pilgrim.passport_number || 'N/A'}</td>
                    <td><span class="badge badge-${statusClass}">${pilgrim.hajj_status}</span></td>
                    <td>
                        <button class="btn-icon btn-pay" onclick="showPaymentModal(${pilgrim.id})">
                            <i class="fas fa-dollar-sign"></i>
                        </button>
                        <button class="btn-icon btn-delete" onclick="deletePilgrim(${pilgrim.id})">
                            <i class="fas fa-trash"></i>
                        </button>
                    </td>
                </tr>
            `;
            tbody.innerHTML += row;
        });
    } catch (error) {
        console.error('Error searching pilgrims:', error);
    }
});

function showAddPilgrimModal() {
    document.getElementById('addPilgrimModal').style.display = 'block';
}

function closeModal(modalId) {
    document.getElementById(modalId).style.display = 'none';
}

document.getElementById('addPilgrimForm').addEventListener('submit', async (e) => {
    e.preventDefault();

    const formData = new FormData(e.target);
    const pilgrimData = {
        name: formData.get('name'),
        age: parseInt(formData.get('age')),
        gender: formData.get('gender'),
        country: formData.get('country'),
        phone: formData.get('phone'),
        email: formData.get('email'),
        passport_number: formData.get('passport_number'),
        group_number: parseInt(formData.get('group_number')) || null,
        is_elderly: formData.get('is_elderly') === 'on',
        is_disabled: formData.get('is_disabled') === 'on'
    };

    try {
        const response = await fetch(`${API_URL}/pilgrims`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${authToken}`
            },
            body: JSON.stringify(pilgrimData)
        });

        const result = await response.json();

        if (response.ok) {
            alert('Pilgrim registered successfully!');
            closeModal('addPilgrimModal');
            e.target.reset();
            loadPilgrims();
            loadDashboardData();
        } else {
            alert(result.error || 'Failed to register pilgrim');
        }
    } catch (error) {
        alert('Error registering pilgrim');
        console.error(error);
    }
});

async function deletePilgrim(id) {
    if (!confirm('Are you sure you want to delete this pilgrim?')) return;

    try {
        const response = await fetch(`${API_URL}/pilgrims/${id}`, {
            method: 'DELETE',
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        if (response.ok) {
            alert('Pilgrim deleted successfully');
            loadPilgrims();
            loadDashboardData();
        } else {
            alert('Failed to delete pilgrim');
        }
    } catch (error) {
        console.error('Error deleting pilgrim:', error);
    }
}

async function loadPayments() {
    try {
        const response = await fetch(`${API_URL}/payments`, {
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        const payments = await response.json();
        const tbody = document.getElementById('paymentsTableBody');
        tbody.innerHTML = '';

        payments.forEach(payment => {
            const statusClass = payment.payment_status === 'Paid' ? 'success' :
                               payment.payment_status === 'Partial' ? 'warning' : 'danger';

            const row = `
                <tr>
                    <td>${payment.id}</td>
                    <td>${payment.pilgrim_name}</td>
                    <td>${payment.passport_number || 'N/A'}</td>
                    <td>$${parseFloat(payment.total_amount).toFixed(2)}</td>
                    <td>$${parseFloat(payment.paid_amount).toFixed(2)}</td>
                    <td>$${parseFloat(payment.remaining_amount).toFixed(2)}</td>
                    <td><span class="badge badge-${statusClass}">${payment.payment_status}</span></td>
                    <td>
                        <button class="btn-icon btn-pay" onclick="showPaymentModal(${payment.pilgrim_id})">
                            <i class="fas fa-plus"></i> Add Payment
                        </button>
                    </td>
                </tr>
            `;
            tbody.innerHTML += row;
        });
    } catch (error) {
        console.error('Error loading payments:', error);
    }
}

function showPaymentModal(pilgrimId) {
    document.getElementById('paymentPilgrimId').value = pilgrimId;
    document.getElementById('paymentModal').style.display = 'block';
}

document.getElementById('paymentForm').addEventListener('submit', async (e) => {
    e.preventDefault();

    const pilgrimId = document.getElementById('paymentPilgrimId').value;
    const amount = document.getElementById('paymentAmount').value;
    const paymentMethod = document.getElementById('paymentMethod').value;
    const transactionId = document.getElementById('transactionId').value;

    try {
        const response = await fetch(`${API_URL}/payments`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${authToken}`
            },
            body: JSON.stringify({
                pilgrim_id: pilgrimId,
                amount: parseFloat(amount),
                payment_method: paymentMethod,
                transaction_id: transactionId
            })
        });

        if (response.ok) {
            alert('Payment recorded successfully!');
            closeModal('paymentModal');
            e.target.reset();
            loadPayments();
            loadDashboardData();
        } else {
            const result = await response.json();
            alert(result.error || 'Failed to record payment');
        }
    } catch (error) {
        alert('Error recording payment');
        console.error(error);
    }
});

async function loadTransportationQueue() {
    try {
        const response = await fetch(`${API_URL}/transportation-queue`, {
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        const queue = await response.json();
        const tbody = document.getElementById('transportationTableBody');
        tbody.innerHTML = '';

        queue.forEach((item, index) => {
            const priorityText = item.priority_level === 1 ? 'High (Disabled)' :
                                item.priority_level === 2 ? 'Medium (Elderly)' : 'Normal';
            const priorityClass = item.priority_level === 1 ? 'danger' :
                                 item.priority_level === 2 ? 'warning' : 'info';

            const row = `
                <tr>
                    <td>${index + 1}</td>
                    <td>${item.name}</td>
                    <td>${item.age}</td>
                    <td><span class="badge badge-${priorityClass}">${priorityText}</span></td>
                    <td>${item.destination || 'Not Set'}</td>
                    <td><span class="badge badge-info">${item.status}</span></td>
                    <td>
                        <button class="btn-icon btn-pay" onclick="boardPilgrim(${item.id})">
                            <i class="fas fa-check"></i> Board
                        </button>
                    </td>
                </tr>
            `;
            tbody.innerHTML += row;
        });
    } catch (error) {
        console.error('Error loading transportation queue:', error);
    }
}

async function boardPilgrim(queueId) {
    try {
        const response = await fetch(`${API_URL}/transportation-queue/${queueId}/board`, {
            method: 'PUT',
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        if (response.ok) {
            alert('Pilgrim boarded successfully!');
            loadTransportationQueue();
            loadDashboardData();
        } else {
            alert('Failed to board pilgrim');
        }
    } catch (error) {
        console.error('Error boarding pilgrim:', error);
    }
}

async function loadAccommodations() {
    try {
        const response = await fetch(`${API_URL}/accommodations`, {
            headers: { 'Authorization': `Bearer ${authToken}` }
        });

        const accommodations = await response.json();
        const grid = document.getElementById('accommodationsGrid');
        grid.innerHTML = '';

        accommodations.forEach(accom => {
            const occupancyPercent = (accom.occupied / accom.capacity * 100).toFixed(1);
            const available = accom.capacity - accom.occupied;

            const card = `
                <div class="accommodation-card">
                    <h3><i class="fas fa-hotel"></i> ${accom.location}</h3>
                    <div class="accommodation-info">
                        <div class="info-row">
                            <label>Capacity:</label>
                            <span>${accom.capacity}</span>
                        </div>
                        <div class="info-row">
                            <label>Occupied:</label>
                            <span>${accom.occupied}</span>
                        </div>
                        <div class="info-row">
                            <label>Available:</label>
                            <span>${available}</span>
                        </div>
                        <div class="info-row">
                            <label>Price per Person:</label>
                            <span>$${parseFloat(accom.price_per_person).toFixed(2)}</span>
                        </div>
                    </div>
                    <div class="progress-bar" style="margin-top: 15px;">
                        <div class="progress-fill" style="width: ${occupancyPercent}%"></div>
                    </div>
                    <small style="display: block; margin-top: 5px; text-align: center; color: var(--text-secondary);">
                        ${occupancyPercent}% Occupied
                    </small>
                </div>
            `;
            grid.innerHTML += card;
        });
    } catch (error) {
        console.error('Error loading accommodations:', error);
    }
}

window.onclick = function(event) {
    if (event.target.classList.contains('modal')) {
        event.target.style.display = 'none';
    }
}
