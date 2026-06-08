# Smart University System - User Menu Guide

## Overview
This is a comprehensive menu-driven system for managing university operations. The system provides an intuitive interface for managing students, courses, and campus navigation.

## Main Menu Structure

### 1. Student Management
Manage all student-related operations:

#### Sub-Menu Options:
1. **Add New Student**
   - Enter Roll Number (integer)
   - Enter Name (string)
   - Enter Department (string)
   - Enter CGPA (0.0 - 4.0)
   
2. **Search Student by Roll Number**
   - Enter Roll Number to find specific student
   - Displays complete student information
   
3. **Search Student by Name**
   - Enter student name to search
   - Displays complete student information
   
4. **Update Student CGPA**
   - Enter Roll Number
   - Enter new CGPA value (0.0 - 4.0)
   - Updates and confirms the change
   
5. **Delete Student Record**
   - Enter Roll Number
   - Shows student info for confirmation
   - Requires confirmation (y/n) before deletion
   
6. **Display Student Information**
   - Enter Roll Number
   - Shows detailed student record
   
7. **Back to Main Menu**

---

### 2. Course Registration Management
Handle course registrations for students:

#### Sub-Menu Options:
1. **Register Course for Student**
   - Enter Student Roll Number
   - System verifies student exists
   - Enter Course Code (e.g., "CSC 101")
   - Enter Course Name (e.g., "Data Structures")
   - Registers course and confirms
   
2. **Drop Course for Student**
   - Enter Student Roll Number
   - System shows current registered courses
   - Enter Course Code to drop
   - Confirms course removal
   
3. **View Student's Registered Courses**
   - Enter Student Roll Number
   - Displays all registered courses with codes and names
   
4. **Back to Main Menu**

---

### 3. Campus Navigation System
Find shortest routes between campus locations using Dijkstra's algorithm:

#### Available Locations:
- Gate_A
- Admin_Block
- CS_Department
- Central_Library
- Auditorium
- Student_Cafeteria

#### Sub-Menu Options:
1. **Find Shortest Route**
   - Enter Starting Location (exact name)
   - Enter Destination (exact name)
   - System calculates and displays:
     * Shortest distance in meters
     * Complete path with all intermediate stops
   
2. **Back to Main Menu**

**Note:** Location names are case-sensitive. Use underscore (_) not spaces.

---

### 4. Save & Exit
- Saves all student data to file
- Ensures data persistence
- Safely exits the program

---

## Data Structures Used

### Module 1: Student Management
- **Dynamic Array**: Stores student records with automatic resizing
- **Linear Search**: For finding students by roll number or name
- **File I/O**: Persistent storage in students.txt

### Module 2: Course Registration
- **Singly Linked List**: Manages course lists for each student
- **Efficient insertion/deletion**: O(1) operations after finding node

### Module 3: Campus Navigation
- **Graph (Adjacency List)**: Represents campus layout
- **Dijkstra's Algorithm**: Finds shortest paths
- **Complexity**: O((V+E) log V)

---

## Usage Tips

1. **Starting the System**
   ```
   ./university.exe
   ```
   System automatically loads existing student records.

2. **Adding Students First**
   Before registering courses, ensure students are added to the system.

3. **Navigation Location Names**
   - Use exact names as shown in the menu
   - Names are case-sensitive
   - Use underscores: `Gate_A` not `Gate A`

4. **Data Persistence**
   - Always use "Save & Exit" (Option 4) to save changes
   - Data is saved to `students.txt`
   - Course registrations are stored within student records

5. **Input Validation**
   - System validates CGPA range (0.0 - 4.0)
   - Confirms student existence before operations
   - Requires confirmation for deletions

---

## Error Handling

The system handles:
- Invalid menu choices
- Non-existent students
- Invalid CGPA values
- Invalid navigation locations
- Input type mismatches

All errors display clear messages and allow you to retry.

---

## Example Workflow

### Adding a Student and Registering Courses:

1. Main Menu → Select `1` (Student Management)
2. Select `1` (Add New Student)
   - Roll No: `101`
   - Name: `John Doe`
   - Department: `Computer Science`
   - CGPA: `3.5`
3. Back to Main Menu (Option `7`)
4. Select `2` (Course Registration)
5. Select `1` (Register Course)
   - Roll No: `101`
   - Course Code: `CSC 101`
   - Course Name: `Data Structures`
6. Select `3` (View Courses) to verify
7. Back to Main Menu and Save & Exit

---

## Technical Implementation

- **Language**: C++11
- **Build Command**: `g++ -std=c++11 main.cpp -o university.exe`
- **Platform**: Windows (PowerShell)

---

## Files Structure

```
Smart University System/
├── main.cpp                    # Menu-driven interface
├── models/
│   ├── Student.hpp            # Student structure
│   └── Course.hpp             # Course node structure
├── modules/
│   ├── StudentManager.hpp     # Student operations
│   ├── CourseManager.hpp      # Course operations
│   └── CampusNavigator.hpp    # Navigation system
├── data_structures/
│   ├── DynamicArray.hpp       # Dynamic array implementation
│   ├── CourseLinkedList.hpp   # Linked list for courses
│   └── CampusGraph.hpp        # Graph for navigation
├── utils/
│   └── FileManager.hpp        # File I/O operations
└── students.txt               # Persistent data storage
```

---

## Future Enhancements (Remaining Modules)

According to the project requirements, the following modules can be added:

- **Module 4**: Library Management (BST/AVL, Hash Table, Queue)
- **Module 5**: Complaint System (Queue, Circular Queue, Priority Heap)
- **Module 6**: Undo/Redo System (Stack)
- **Module 7**: Navigation History (Doubly Linked List)
- **Module 8**: Sorting & Searching Engine (Multiple algorithms)

---

## Contact & Support

For issues or questions about the system, refer to:
- Source code comments
- DSA Project requirements document
- Module-specific documentation in header files
