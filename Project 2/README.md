# Smart Hajj Management System

## Data Structures Course Project

### Overview
The Smart Hajj Management System is a comprehensive GUI-based application designed to manage Hajj-related operations using fundamental Data Structures. This system simulates real-world Hajj management scenarios including pilgrim registration, transportation scheduling, accommodation allocation, and ritual tracking.

---

## Features

### 1. Pilgrim Registration Module
- Register new pilgrims with complete information
- Automatic ID generation
- Support for elderly and disabled pilgrim identification
- Dynamic storage using Linked Lists

### 2. Transportation Management
- Queue-based bus boarding system
- Configurable bus capacity (default: 50 pilgrims)
- Real-time queue visualization
- Automatic bus allocation calculation

### 3. Priority Queue System
- Special handling for elderly pilgrims (65+ years)
- Priority processing for disabled pilgrims
- Priority levels:
  - Priority 1: Disabled pilgrims
  - Priority 2: Elderly pilgrims (65+)
  - Priority 3: Regular pilgrims

### 4. Accommodation Management
- Array-based capacity management
- Pre-configured accommodations:
  - Makkah hotels
  - Mina tent camps
  - Arafat camps
  - Muzdalifah areas
- Automatic assignment and occupancy tracking

### 5. Ritual (Manasik) Tracking
- Stack-based ritual completion tracking
- Seven main Hajj rituals:
  1. Ihram (State of Consecration)
  2. Tawaf (Circumambulation of Kaaba)
  3. Sa'i (Walking between Safa and Marwa)
  4. Standing at Arafat
  5. Muzdalifah (Night Stay)
  6. Rami (Stoning the Devil)
  7. Sacrifice (Qurbani)
- Timestamp recording for each ritual

### 6. Search and Sort Module
- Binary Search Tree for fast ID-based searching
- Linear search for name-based queries
- Bubble Sort for age-based sorting
- Selection Sort for ID-based sorting
- BST in-order traversal for sorted display

### 7. Reporting System
- Comprehensive system statistics
- Real-time progress tracking
- Accommodation occupancy reports
- Queue status monitoring

---

## Data Structures Implementation

### Data Structures Used

| Data Structure | Application | Implementation |
|----------------|-------------|----------------|
| **Structure (struct)** | Pilgrim information storage | `Pilgrim` struct with 9 fields |
| **Linked List** | Dynamic pilgrim registration | `PilgrimLinkedList` class |
| **Queue** | Transportation management | `TransportationQueue` class |
| **Priority Queue** | Elderly/disabled handling | `PriorityQueue` class |
| **Array** | Fixed accommodation capacity | `Accommodation[MAX_ACCOMMODATIONS]` |
| **Stack** | Ritual completion tracking | `RitualStack` class |
| **Binary Search Tree** | Fast pilgrim searching | `PilgrimBST` class |
| **Sorting Algorithms** | Data organization | Bubble Sort, Selection Sort |
| **Searching Algorithms** | Record retrieval | Linear Search, BST Search |
| **Recursion** | Tree operations | BST insert, search, traversal |

---

## System Architecture

```
Smart Hajj Management System
│
├── Pilgrim Management
│   ├── Linked List (Registration)
│   └── BST (Fast Searching)
│
├── Transportation
│   ├── Regular Queue
│   └── Priority Queue
│
├── Accommodation
│   └── Array-based Management
│
├── Ritual Tracking
│   └── Stack-based Completion
│
└── Utilities
    ├── Sorting (Bubble, Selection)
    └── Searching (Linear, BST)
```

---

## How to Compile and Run

### Requirements
- C++ Compiler (GCC, MinGW, or MSVC)
- Windows OS (for colored console output)
- C++11 or higher

### Compilation

#### Using GCC/MinGW:
```bash
g++ -std=c++11 HajjManagementSystem.cpp -o HajjManagement.exe
```

#### Using MSVC (Visual Studio):
```bash
cl /EHsc HajjManagementSystem.cpp
```

### Running the Program:
```bash
./HajjManagement.exe
```

---

## User Guide

### Main Menu Options

1. **Pilgrim Registration**
   - Enter pilgrim details (name, age, gender, country)
   - System automatically assigns ID and accommodation
   - Identifies elderly (65+) and disabled pilgrims

2. **View All Pilgrims**
   - Displays complete pilgrim list
   - Shows ID, name, age, gender, country, and priority status

3. **Search Pilgrim**
   - Option 1: Search by ID (using BST - O(log n))
   - Option 2: Search by Name (using Linear Search)

4. **Transportation Management**
   - Add pilgrims to queue
   - View current queue
   - Board bus (processes up to 50 pilgrims)

5. **Priority Queue**
   - Add elderly/disabled pilgrims
   - View priority queue
   - Process high-priority pilgrims first

6. **Accommodation Management**
   - View all accommodations
   - Check capacity and occupancy
   - See available slots

7. **Ritual Tracking**
   - Mark rituals as completed
   - View completion history (most recent first)
   - Track Hajj progress

8. **Sort Pilgrims**
   - Sort by ID (Selection Sort)
   - Sort by Age (Bubble Sort)
   - Display sorted by ID (BST in-order)

9. **Generate Reports**
   - Total pilgrims registered
   - Queue statistics
   - Hajj completion progress
   - System overview

10. **Exit**
    - Safely exit the system

---

## Code Structure

### Classes Implemented

1. **PilgrimLinkedList**
   - Dynamic pilgrim storage
   - Methods: `addPilgrim()`, `displayAll()`, `searchByID()`

2. **TransportationQueue**
   - FIFO queue for bus boarding
   - Methods: `enqueue()`, `dequeue()`, `boardBus()`

3. **PriorityQueue**
   - Priority-based queue
   - Methods: `enqueue(id, priority)`, `dequeue()`

4. **AccommodationManager**
   - Array-based room allocation
   - Methods: `assignAccommodation()`, `displayAll()`

5. **RitualStack**
   - LIFO stack for ritual tracking
   - Methods: `push()`, `displayRituals()`

6. **PilgrimBST**
   - Binary Search Tree for fast searching
   - Methods: `insert()`, `search()`, `displayInOrder()`

---

## Sample Usage

### Example 1: Register a Pilgrim
```
Enter Name: Ahmed Ali
Enter Age: 45
Enter Gender: M
Enter Country: Saudi Arabia
Is Elderly: 0
Is Disabled: 0
Enter Group Number: 101

✓ Pilgrim registered successfully!
  Assigned ID: 1001
  Accommodation ID: 1
```

### Example 2: Transportation Queue
```
Add Pilgrim ID 1001 to queue
Add Pilgrim ID 1002 to queue
Board Bus → 50 pilgrims board
Remaining: 2 in queue
```

### Example 3: Ritual Tracking
```
Mark "Tawaf" as completed
Mark "Sa'i" as completed
Progress: 2/7 rituals (28%)
```

---

## Time Complexity Analysis

| Operation | Data Structure | Time Complexity |
|-----------|----------------|-----------------|
| Add Pilgrim | Linked List | O(n) |
| Search by ID | BST | O(log n) average |
| Search by Name | Linear Search | O(n) |
| Enqueue Transport | Queue | O(1) |
| Dequeue Transport | Queue | O(1) |
| Priority Enqueue | Priority Queue | O(n) |
| Mark Ritual | Stack | O(1) |
| Sort by Age | Bubble Sort | O(n²) |
| Sort by ID | Selection Sort | O(n²) |
| Assign Accommodation | Array | O(n) |

---

## Space Complexity

- **Pilgrim List**: O(n) where n = number of pilgrims
- **Transportation Queue**: O(m) where m = queue size
- **Priority Queue**: O(p) where p = priority pilgrim count
- **BST**: O(n) for n pilgrims
- **Accommodation Array**: O(MAX_ACCOMMODATIONS) = O(100)
- **Ritual Stack**: O(7) for 7 rituals

---

## Key Learning Outcomes

This project demonstrates:
1. Practical implementation of Linked Lists for dynamic data
2. Queue and Priority Queue for scheduling systems
3. Stack for tracking sequential operations
4. BST for efficient searching
5. Array for fixed-capacity management
6. Sorting algorithms (Bubble Sort, Selection Sort)
7. Searching algorithms (Linear, BST)
8. Recursion in tree operations
9. Object-Oriented Programming principles
10. GUI-based console application design

---

## Future Enhancements

1. **Database Integration**
   - MySQL/PostgreSQL for persistent storage
   - SQL queries for advanced reporting

2. **Web Interface**
   - RESTful API backend
   - React/Angular frontend
   - Mobile responsive design

3. **Real-Time Tracking**
   - GPS integration
   - Live location monitoring
   - Geofencing for ritual sites

4. **RFID Integration**
   - Smart ID cards
   - Automated check-in
   - Crowd density management

5. **Advanced Analytics**
   - Predictive modeling
   - Route optimization
   - Capacity planning

6. **Multi-Language Support**
   - Arabic, English, Urdu, Turkish
   - Right-to-left text support

7. **Emergency Management**
   - Medical emergency alerts
   - Lost pilgrim tracking
   - Emergency evacuation planning

---

## Project Team

**Course**: Data Structures
**Project Type**: GUI-based Console Application
**Language**: C++
**Paradigm**: Object-Oriented Programming

---

## Technical Specifications

- **Language**: C++ (C++11 standard)
- **Platform**: Windows
- **GUI**: Console-based with colored output
- **Memory Management**: Dynamic memory allocation with proper cleanup
- **Error Handling**: Input validation and boundary checks
- **Code Style**: Object-oriented with encapsulation

---

## Testing Checklist

- [ ] Register multiple pilgrims
- [ ] Search by ID and name
- [ ] Add pilgrims to transportation queue
- [ ] Board bus with capacity constraints
- [ ] Add elderly/disabled to priority queue
- [ ] Process priority pilgrims
- [ ] View accommodation status
- [ ] Mark all 7 rituals as completed
- [ ] Sort pilgrims by age and ID
- [ ] Generate system reports
- [ ] Test with edge cases (empty lists, full capacity)

---

## Troubleshooting

### Issue: Colored text not displaying
**Solution**: Run on Windows terminal with color support enabled

### Issue: Input not working properly
**Solution**: Check for `cin.ignore()` after numeric inputs

### Issue: Memory leaks
**Solution**: Destructors properly implemented for all dynamic structures

---

## License

This project is developed for educational purposes as part of the Data Structures course curriculum.

---

## Acknowledgments

- Course instructors for project requirements
- Data Structures textbook references
- Islamic Hajj guidelines for ritual definitions

---

## Contact

For questions or suggestions about this project, please contact your course instructor.

---

**May Allah accept the Hajj of all pilgrims!**
