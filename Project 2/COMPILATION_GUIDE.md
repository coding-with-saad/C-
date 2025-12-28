# Compilation and Testing Guide
## Smart Hajj Management System

---

## Compilation Instructions

### Method 1: Using GCC/MinGW (Recommended)

#### Step 1: Install MinGW
1. Download MinGW from: https://sourceforge.net/projects/mingw/
2. Install and add to PATH environment variable

#### Step 2: Compile
```bash
g++ -std=c++11 HajjManagementSystem.cpp -o HajjManagement.exe
```

#### Step 3: Run
```bash
./HajjManagement.exe
```

---

### Method 2: Using Microsoft Visual Studio

#### Step 1: Open Developer Command Prompt
- Search "Developer Command Prompt" in Start Menu

#### Step 2: Navigate to Project Directory
```bash
cd "F:\claude cli 20 12 2025"
```

#### Step 3: Compile
```bash
cl /EHsc HajjManagementSystem.cpp
```

#### Step 4: Run
```bash
HajjManagementSystem.exe
```

---

### Method 3: Using Visual Studio IDE

1. Create new C++ Console Project
2. Add `HajjManagementSystem.cpp` to project
3. Build Solution (Ctrl + Shift + B)
4. Run (Ctrl + F5)

---

### Method 4: Using Code::Blocks

1. File → New → Project → Console Application
2. Add existing file: `HajjManagementSystem.cpp`
3. Build → Build (Ctrl + F9)
4. Build → Run (Ctrl + F10)

---

### Method 5: Using Dev-C++

1. File → New → Project → Console Application
2. Add file to project
3. Execute → Compile (F9)
4. Execute → Run (F10)

---

## Compilation Flags Explained

```bash
g++ -std=c++11 HajjManagementSystem.cpp -o HajjManagement.exe
```

- `-std=c++11`: Use C++11 standard (required for nullptr)
- `-o HajjManagement.exe`: Output executable name
- `-Wall`: Enable all warnings (optional but recommended)
- `-O2`: Optimization level 2 (optional)

### With All Options:
```bash
g++ -std=c++11 -Wall -O2 HajjManagementSystem.cpp -o HajjManagement.exe
```

---

## Testing the System

### Test Case 1: Basic Registration
```
Action: Register 5 pilgrims with varied data
Expected: All pilgrims get unique IDs (1001-1005)
Verify: View All Pilgrims shows complete list
```

### Test Case 2: Search Functionality
```
Action: Search by ID 1001 (BST)
Expected: Pilgrim details displayed correctly

Action: Search by name "Ahmed Ali"
Expected: Correct pilgrim found
```

### Test Case 3: Transportation Queue
```
Action: Add 100 pilgrims to queue
Action: Board bus (capacity 50)
Expected: 50 board, 50 remain in queue

Action: Board bus again
Expected: Remaining 50 board, queue empty
```

### Test Case 4: Priority Queue
```
Action: Add elderly pilgrim (age 70)
Action: Add disabled pilgrim
Action: Add regular pilgrim
Expected: Disabled processed first, then elderly, then regular
```

### Test Case 5: Accommodation
```
Action: Register 160 pilgrims
Expected: First 150 get accommodation
Expected: Last 10 show "No accommodation available"
Verify: Accommodation status shows correct occupancy
```

### Test Case 6: Ritual Tracking
```
Action: Mark all 7 rituals as completed
Expected: Stack shows rituals in reverse order (LIFO)
Expected: Progress shows 100%
```

### Test Case 7: Sorting
```
Action: Sort by Age (Bubble Sort)
Expected: Pilgrims ordered youngest to oldest

Action: Sort by ID (Selection Sort)
Expected: Pilgrims ordered by ID

Action: BST In-Order
Expected: Pilgrims sorted by ID
```

### Test Case 8: Edge Cases
```
Test: Empty list operations
Test: Search in empty database
Test: Board bus with empty queue
Test: Process priority queue when empty
Test: Full accommodation capacity
```

---

## Sample Test Data

### Pilgrim 1:
```
Name: Ahmed Ali
Age: 45
Gender: M
Country: Saudi Arabia
Elderly: No
Disabled: No
Group: 101
```

### Pilgrim 2:
```
Name: Fatima Hassan
Age: 68
Gender: F
Country: Egypt
Elderly: Yes
Disabled: No
Group: 102
```

### Pilgrim 3:
```
Name: Muhammad Khan
Age: 35
Gender: M
Country: Pakistan
Elderly: No
Disabled: Yes
Group: 103
```

### Pilgrim 4:
```
Name: Aisha Rahman
Age: 28
Gender: F
Country: Bangladesh
Elderly: No
Disabled: No
Group: 104
```

### Pilgrim 5:
```
Name: Ibrahim Yusuf
Age: 72
Gender: M
Country: Turkey
Elderly: Yes
Disabled: No
Group: 105
```

---

## Expected Output Examples

### Registration Output:
```
========== PILGRIM REGISTRATION ==========

Enter Name: Ahmed Ali
Enter Age: 45
Enter Gender (M/F): M
Enter Country: Saudi Arabia
Is Elderly (65+)? (1-Yes/0-No): 0
Is Disabled? (1-Yes/0-No): 0
Enter Group Number: 101

✓ Pilgrim registered successfully!
  Assigned ID: 1001
  Accommodation ID: 1
```

### View All Output:
```
========== REGISTERED PILGRIMS ==========

ID      Name                     Age   Gender  Country             Priority
--------------------------------------------------------------------------------
1001    Ahmed Ali                45    Male    Saudi Arabia        Normal
1002    Fatima Hassan            68    Female  Egypt               Elderly
1003    Muhammad Khan            35    Male    Pakistan            Disabled
1004    Aisha Rahman             28    Female  Bangladesh          Normal
1005    Ibrahim Yusuf            72    Male    Turkey              Elderly

Total Pilgrims: 5
```

### Transportation Queue:
```
========== TRANSPORTATION QUEUE ==========
Queue Size: 5 | Bus Capacity: 50
Buses Needed: 1

Pilgrims in Queue:
1. ID: 1001 - Ahmed Ali
2. ID: 1002 - Fatima Hassan
3. ID: 1003 - Muhammad Khan
4. ID: 1004 - Aisha Rahman
5. ID: 1005 - Ibrahim Yusuf
```

### Priority Queue:
```
========== PRIORITY TRANSPORTATION QUEUE ==========
Queue Size: 2

Priority Pilgrims:
1. [Priority 1] ID: 1003 - Muhammad Khan (Disabled)
2. [Priority 2] ID: 1002 - Fatima Hassan (Elderly)
```

### Accommodation Status:
```
========== ACCOMMODATION STATUS ==========

ID: 1 | Makkah - Hotel Al-Safa | Capacity: 150 | Occupied: 45 | Available: 105
ID: 2 | Makkah - Hotel Dar Al-Tawhid | Capacity: 200 | Occupied: 0 | Available: 200
ID: 3 | Mina - Tent Camp A | Capacity: 300 | Occupied: 0 | Available: 300
ID: 4 | Mina - Tent Camp B | Capacity: 300 | Occupied: 0 | Available: 300
ID: 5 | Arafat - Tent Camp | Capacity: 500 | Occupied: 0 | Available: 500
ID: 6 | Muzdalifah - Open Area | Capacity: 400 | Occupied: 0 | Available: 400

Total Accommodations: 6
```

### System Reports:
```
========== SYSTEM REPORTS ==========

📊 Total Pilgrims Registered: 150
🚌 Pilgrims in Transportation Queue: 25
⚠️  Pilgrims in Priority Queue: 10
🕋 Rituals Completed: 5 / 7

🔄 Hajj Progress: 71%

========================================
```

---

## Common Compilation Errors and Solutions

### Error 1: 'nullptr' was not declared
```
Solution: Use -std=c++11 flag
g++ -std=c++11 HajjManagementSystem.cpp -o HajjManagement.exe
```

### Error 2: Windows.h not found
```
Solution: Compile on Windows OS or comment out Windows-specific code
```

### Error 3: Undefined reference to WinMain
```
Solution: Ensure main() function exists and is properly defined
```

### Error 4: strcpy unsafe warnings
```
Solution: Add flag to suppress or use strcpy_s
// For GCC: warnings can be ignored
// For MSVC: #define _CRT_SECURE_NO_WARNINGS
```

---

## Performance Testing

### Recommended Test Scenarios:

1. **Small Scale**: 10-50 pilgrims
2. **Medium Scale**: 100-500 pilgrims
3. **Large Scale**: 1000+ pilgrims

### Metrics to Track:
- Registration time
- Search time (BST vs Linear)
- Sort time (different algorithms)
- Memory usage
- Queue processing speed

---

## Debugging Tips

### Enable Debug Mode:
```cpp
#define DEBUG 1

#ifdef DEBUG
    cout << "Debug: Variable value = " << value << endl;
#endif
```

### Common Issues:

1. **Segmentation Fault**
   - Check nullptr access
   - Verify BST traversal
   - Check linked list operations

2. **Infinite Loop**
   - Check while conditions
   - Verify queue operations
   - Check linked list traversal

3. **Memory Leak**
   - Verify all new has corresponding delete
   - Check destructor implementations
   - Use valgrind (Linux) or Visual Studio memory profiler

---

## Platform-Specific Notes

### Windows:
- Colored console output works natively
- Windows.h required for SetConsoleTextAttribute

### Linux/Mac:
- Replace Windows.h with ANSI color codes
- Example:
```cpp
void setColor(int color) {
    // ANSI color codes
    cout << "\033[1;3" << color << "m";
}
```

---

## Submission Checklist

- [ ] Source code file (HajjManagementSystem.cpp)
- [ ] README.md documentation
- [ ] Compilation guide (this file)
- [ ] Executable file (.exe)
- [ ] Test results screenshots
- [ ] Project report (if required)
- [ ] UML diagrams (optional)
- [ ] Presentation slides (if required)

---

## Additional Resources

### C++ References:
- https://en.cppreference.com/
- https://www.cplusplus.com/

### Data Structures:
- Linked Lists: https://www.geeksforgeeks.org/data-structures/linked-list/
- Queues: https://www.geeksforgeeks.org/queue-data-structure/
- Stacks: https://www.geeksforgeeks.org/stack-data-structure/
- BST: https://www.geeksforgeeks.org/binary-search-tree-data-structure/

---

## Version Information

- **Project Version**: 1.0
- **Language**: C++11
- **Compiler Tested**: GCC 11.2, MSVC 2019
- **Platform**: Windows 10/11
- **Date**: December 2025

---

## Support

If you encounter any issues:
1. Check this compilation guide
2. Verify compiler version and flags
3. Review error messages carefully
4. Check platform compatibility
5. Contact course instructor

---

**Happy Coding!**
