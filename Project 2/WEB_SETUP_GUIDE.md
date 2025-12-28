# Smart Hajj Management System - Web GUI Setup Guide

## Complete Installation and Setup Instructions

---

## System Overview

This is a modern web-based Hajj Management System with:
- **Backend**: Node.js + Express + SQLite Database
- **Frontend**: HTML5 + CSS3 + Vanilla JavaScript
- **Features**:
  - Pilgrim Registration & Management
  - Payment Tracking with Installments
  - Transportation Queue Management
  - Accommodation Management
  - Ritual Progress Tracking
  - Beautiful Dashboard with Statistics

---

## Prerequisites

### Required Software:

1. **Node.js** (v14 or higher)
   - Download from: https://nodejs.org/
   - Choose LTS (Long Term Support) version
   - Verify installation: `node --version`

2. **npm** (comes with Node.js)
   - Verify installation: `npm --version`

3. **Web Browser** (Chrome, Firefox, Edge - any modern browser)

4. **Text Editor** (Optional - VS Code, Notepad++, Sublime)

---

## Installation Steps

### Step 1: Install Node.js

1. Go to https://nodejs.org/
2. Download the LTS version for Windows
3. Run the installer
4. Click "Next" through the installation wizard
5. Accept the license agreement
6. Use default installation path
7. Make sure "Add to PATH" is checked
8. Complete installation

### Step 2: Verify Installation

Open Command Prompt (cmd) and run:
```bash
node --version
npm --version
```

You should see version numbers like:
```
v18.17.0
9.6.7
```

### Step 3: Install Backend Dependencies

1. Open Command Prompt
2. Navigate to backend folder:
```bash
cd "F:\claude cli 20 12 2025\backend"
```

3. Install dependencies:
```bash
npm install
```

This will install:
- express (Web framework)
- cors (Cross-origin support)
- body-parser (Request parsing)
- sqlite3 (Database)
- bcrypt (Password hashing)
- jsonwebtoken (Authentication)

Wait for installation to complete (may take 2-3 minutes).

---

## Running the Application

### Step 1: Start the Backend Server

1. Open Command Prompt
2. Navigate to backend folder:
```bash
cd "F:\claude cli 20 12 2025\backend"
```

3. Start the server:
```bash
npm start
```

You should see:
```
Server running on http://localhost:3000
Default login: username=admin, password=admin123
```

**IMPORTANT**: Keep this Command Prompt window open! The server must run continuously.

### Step 2: Open the Frontend

1. Open Windows Explorer
2. Navigate to: `F:\claude cli 20 12 2025\frontend`
3. Double-click `index.html`

OR

Right-click `index.html` → Open with → Chrome (or your preferred browser)

### Step 3: Login

On the login page:
- **Username**: `admin`
- **Password**: `admin123`

Click "Login" button.

---

## Using the System

### Dashboard

The dashboard shows:
- **Total Pilgrims**: Number of registered pilgrims
- **Completed Hajj**: Pilgrims who finished Hajj
- **Total Revenue**: All payments received
- **Pending Payments**: Outstanding payment amounts
- **Accommodation Status**: Occupancy rate
- **Transportation Queue**: Waiting pilgrims

### Pilgrim Management

**Add New Pilgrim:**
1. Click "Pilgrims" in sidebar
2. Click "+ Add Pilgrim" button
3. Fill in the form:
   - Full Name (required)
   - Age (required)
   - Gender (required)
   - Country (required)
   - Phone (optional)
   - Email (optional)
   - Passport Number (required, must be unique)
   - Group Number (optional)
   - Check "Elderly" if 65+ years
   - Check "Disabled" if applicable
4. Click "Register Pilgrim"

**Search Pilgrims:**
- Use the search box at top
- Search by: Name, Passport Number, or Email
- Results appear instantly

**Delete Pilgrim:**
- Click the red trash icon next to pilgrim
- Confirm deletion

### Payment Management

**View Payments:**
1. Click "Payments" in sidebar
2. See all payment records with:
   - Total amount
   - Paid amount
   - Remaining balance
   - Payment status

**Record Payment:**
1. In Payments page, click "Add Payment" button
2. OR in Pilgrims page, click $ icon next to pilgrim
3. Enter:
   - Amount to Pay
   - Payment Method (Cash, Credit Card, Bank Transfer, Online)
   - Transaction ID (optional)
4. Click "Confirm Payment"

**Payment Status:**
- **Paid**: Fully paid (green)
- **Partial**: Partially paid (yellow)
- **Pending**: No payment yet (red)

### Transportation Queue

**Add to Queue:**
1. Click "Transportation" in sidebar
2. Click "+ Add to Queue"
3. Select pilgrim ID
4. Enter destination
5. System automatically assigns priority:
   - **Priority 1 (High)**: Disabled pilgrims
   - **Priority 2 (Medium)**: Elderly pilgrims
   - **Priority 3 (Normal)**: Regular pilgrims

**Board Pilgrim:**
- Click "Board" button next to pilgrim
- Status changes to "Boarded"
- Pilgrim removed from waiting queue

### Accommodations

**View Accommodations:**
1. Click "Accommodations" in sidebar
2. See all available accommodations:
   - Location
   - Capacity
   - Occupied count
   - Available spaces
   - Price per person
   - Occupancy percentage

**Auto-Assignment:**
- When registering a pilgrim, system automatically assigns accommodation
- Assignment is based on availability
- First available accommodation is selected

### Ritual Tracking

**Track Rituals:**
1. Click "Rituals" in sidebar
2. Select a pilgrim
3. Mark rituals as completed:
   - Ihram (State of Consecration)
   - Tawaf (Circumambulation of Kaaba)
   - Sa'i (Walking between Safa and Marwa)
   - Standing at Arafat
   - Muzdalifah (Night Stay)
   - Rami (Stoning the Devil)
   - Sacrifice (Qurbani)

---

## Database Information

### Database Location
- File: `F:\claude cli 20 12 2025\backend\hajj_management.db`
- Type: SQLite
- Created automatically on first run

### Database Tables

1. **pilgrims** - Pilgrim information
2. **payments** - Payment records
3. **payment_installments** - Payment history
4. **accommodations** - Accommodation details
5. **transportation_queue** - Transportation queue
6. **rituals** - Ritual tracking
7. **users** - System users

### Pre-loaded Data

**Default Accommodations:**
1. Makkah - Hotel Al-Safa (150 capacity, $2500)
2. Makkah - Hotel Dar Al-Tawhid (200 capacity, $3000)
3. Mina - Tent Camp A (300 capacity, $1500)
4. Mina - Tent Camp B (300 capacity, $1500)
5. Arafat - Tent Camp (500 capacity, $1000)
6. Muzdalifah - Open Area (400 capacity, $800)

**Default User:**
- Username: admin
- Password: admin123
- Role: Administrator

---

## API Endpoints

### Authentication
- `POST /api/login` - User login

### Pilgrims
- `GET /api/pilgrims` - Get all pilgrims
- `GET /api/pilgrims/:id` - Get pilgrim by ID
- `POST /api/pilgrims` - Register new pilgrim
- `PUT /api/pilgrims/:id` - Update pilgrim
- `DELETE /api/pilgrims/:id` - Delete pilgrim
- `GET /api/search/pilgrims?q=term` - Search pilgrims

### Payments
- `GET /api/payments` - Get all payments
- `GET /api/payments/pilgrim/:id` - Get payment by pilgrim
- `POST /api/payments` - Record payment

### Transportation
- `GET /api/transportation-queue` - Get queue
- `POST /api/transportation-queue` - Add to queue
- `PUT /api/transportation-queue/:id/board` - Board pilgrim

### Accommodations
- `GET /api/accommodations` - Get all accommodations

### Rituals
- `GET /api/rituals/pilgrim/:id` - Get pilgrim rituals
- `PUT /api/rituals/:id/complete` - Mark ritual complete

### Dashboard
- `GET /api/dashboard/stats` - Get statistics

---

## Troubleshooting

### Problem: "npm is not recognized"
**Solution**: Node.js not installed or not in PATH
1. Reinstall Node.js
2. Make sure "Add to PATH" is checked
3. Restart Command Prompt

### Problem: "Cannot find module 'express'"
**Solution**: Dependencies not installed
```bash
cd backend
npm install
```

### Problem: "Port 3000 is already in use"
**Solution**: Another app using port 3000
1. Close other servers
2. OR change port in `server.js`:
```javascript
const PORT = 3001; // Change to 3001
```
Then update frontend `js/app.js`:
```javascript
const API_URL = 'http://localhost:3001/api';
```

### Problem: "CORS Error" in browser
**Solution**: Backend not running
1. Start backend server first
2. Then open frontend

### Problem: "Login failed"
**Solution**:
1. Check username: `admin`
2. Check password: `admin123`
3. Make sure backend is running
4. Check browser console for errors (F12)

### Problem: Data not loading
**Solution**:
1. Open browser console (F12)
2. Check for errors
3. Verify backend is running
4. Check API_URL in `js/app.js`

### Problem: Database errors
**Solution**:
1. Delete `hajj_management.db` file
2. Restart backend server
3. Database will be recreated

---

## Development Mode

For development with auto-restart on file changes:

1. Install nodemon globally:
```bash
npm install -g nodemon
```

2. Run in dev mode:
```bash
npm run dev
```

---

## Security Notes

### Production Deployment

For production use, change:

1. **Secret Key** in `server.js`:
```javascript
const SECRET_KEY = 'your-very-secure-random-key-here';
```

2. **Admin Password**:
   - Login with default credentials
   - Create new admin user
   - Delete default user

3. **CORS Settings**:
```javascript
app.use(cors({
    origin: 'https://yourdomain.com'
}));
```

---

## Backup and Restore

### Backup Database
Simply copy the file:
```
hajj_management.db
```
to a safe location.

### Restore Database
Replace the current `hajj_management.db` with backup file.

---

## File Structure

```
F:\claude cli 20 12 2025\
│
├── backend/
│   ├── package.json          (Dependencies)
│   ├── server.js              (Main server file)
│   ├── database.js            (Database setup)
│   └── hajj_management.db     (SQLite database)
│
├── frontend/
│   ├── index.html             (Main HTML)
│   ├── css/
│   │   └── style.css          (Styling)
│   └── js/
│       └── app.js             (JavaScript logic)
│
├── HajjManagementSystem.cpp   (Original C++ code)
├── README.md                  (C++ documentation)
└── WEB_SETUP_GUIDE.md         (This file)
```

---

## Features Comparison

### C++ Console vs Web GUI

| Feature | C++ Console | Web GUI |
|---------|-------------|---------|
| Interface | Text-based | Modern Visual |
| Database | In-memory | SQLite (Persistent) |
| Multi-user | No | Yes (with auth) |
| Remote Access | No | Yes (network) |
| Payment Tracking | Basic | Advanced with installments |
| Reports | Text | Visual dashboard |
| Search | Limited | Full-text search |
| Accessibility | Terminal only | Any device with browser |

---

## Advanced Features

### Payment Installments
- Support for partial payments
- Track payment history
- Multiple payment methods
- Transaction references

### Priority System
- Automatic priority assignment
- Disabled: Priority 1
- Elderly: Priority 2
- Regular: Priority 3

### Search Functionality
- Real-time search
- Search by name, passport, email
- Instant results

### Responsive Design
- Works on desktop
- Works on tablet
- Works on mobile

---

## Performance Optimization

For handling large data:

1. **Pagination**: Add limit/offset to queries
2. **Indexing**: SQLite auto-indexes primary keys
3. **Caching**: Browser caches static files
4. **Lazy Loading**: Load data on demand

---

## Browser Compatibility

Tested on:
- Google Chrome (Recommended)
- Mozilla Firefox
- Microsoft Edge
- Safari (Mac/iOS)

Minimum versions:
- Chrome 90+
- Firefox 88+
- Edge 90+
- Safari 14+

---

## Support and Updates

### Getting Help
1. Check this documentation
2. Review error messages in:
   - Browser console (F12)
   - Backend terminal
3. Check API responses

### Future Enhancements
- User roles and permissions
- Email notifications
- PDF report generation
- Data export (Excel, CSV)
- Real-time updates (WebSocket)
- Mobile app version
- QR code check-in
- SMS notifications

---

## License
Educational project for Data Structures course.

---

## Credits
- **Project**: Smart Hajj Management System
- **Version**: 2.0 (Web Edition)
- **Technology**: Node.js, Express, SQLite, HTML5, CSS3, JavaScript
- **Date**: December 2025

---

## Quick Start Summary

1. Install Node.js
2. Open Command Prompt
3. Run: `cd "F:\claude cli 20 12 2025\backend"`
4. Run: `npm install`
5. Run: `npm start`
6. Open `frontend/index.html` in browser
7. Login: admin / admin123
8. Start managing Hajj operations!

---

**May Allah accept everyone's Hajj!**
