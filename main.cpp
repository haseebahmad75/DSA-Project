#include "modules/StudentManager.hpp"
#include "modules/CourseManager.hpp"
#include "modules/CampusNavigator.hpp"
#include "modules/LibraryManager.hpp"
#include "modules/ComplaintManager.hpp"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Function prototypes
void displayMainMenu();
void handleStudentManagement(StudentManager& sm);
void handleCourseManagement(CourseManager& cm, StudentManager& sm);
void handleCampusNavigation(CampusNavigator& cn);
void handleLibraryManagement(LibraryManager& lm);
void handleComplaintTokenManagement(ComplaintManager& cpm);
void clearInputBuffer();
void pauseScreen();

int main() {
    // Initialize all managers
    StudentManager sm;
    sm.InitSystem();
    cout << "[SYSTEM] Student records loaded successfully.\n";
    
    CourseManager cm(sm);
    CampusNavigator cn;
    LibraryManager lm;
    ComplaintManager cpm;
    cout << "[SYSTEM] All systems initialized successfully.\n\n";
    
    int mainChoice;
    bool exitProgram = false;
    
    while (!exitProgram) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> mainChoice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        clearInputBuffer();
        
        switch (mainChoice) {
            case 1:
                handleStudentManagement(sm);
                break;
            case 2:
                handleCourseManagement(cm, sm);
                break;
            case 3:
                handleLibraryManagement(lm);
                break;
            case 4:
                handleComplaintTokenManagement(cpm);
                break;
            case 5:
                handleCampusNavigation(cn);
                break;
            case 6:
                cout << "\n[SYSTEM] Saving all data...\n";
                sm.SaveSystemState();
                cout << "[SYSTEM] Data saved successfully!\n";
                cout << "[SYSTEM] Thank you for using Smart University System!\n";
                cout << "==================================================\n";
                exitProgram = true;
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-6.\n";
                pauseScreen();
        }
    }
    
    return 0;
}

void displayMainMenu() {
    cout << "\n==================================================\n";
    cout << "     SMART UNIVERSITY MANAGEMENT SYSTEM          \n";
    cout << "==================================================\n";
    cout << "1. Student Management\n";
    cout << "2. Course Registration Management\n";
    cout << "3. Library Management System\n";
    cout << "4. Complaint & Token Management\n";
    cout << "5. Campus Navigation System\n";
    cout << "6. Save & Exit\n";
    cout << "==================================================\n";
}

void handleStudentManagement(StudentManager& sm) {
    int choice;
    bool backToMain = false;
    
    while (!backToMain) {
        cout << "\n==================================================\n";
        cout << "           STUDENT MANAGEMENT MENU                \n";
        cout << "==================================================\n";
        cout << "1. Add New Student\n";
        cout << "2. Search Student by Roll Number\n";
        cout << "3. Search Student by Name\n";
        cout << "4. Update Student CGPA\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Display Student Information\n";
        cout << "7. Display All Students\n";
        cout << "8. Sort Students by Roll Number (Bubble Sort)\n";
        cout << "9. Sort Students by CGPA (Selection Sort)\n";
        cout << "--------------------------------------------------\n";
        cout << "10. [UNDO] Undo Last Student Action \n";
        cout << "11. [REDO] Redo Last Student Action \n";
        cout << "--------------------------------------------------\n";
        cout << "12. Back to Main Menu\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // Add New Student
                int rollNo;
                string name, dept;
                float cgpa;
                
                cout << "\n--- Add New Student ---\n";
                cout << "Enter Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Department: ";
                getline(cin, dept);
                
                cout << "Enter CGPA (0.0 - 4.0): ";
                cin >> cgpa;
                clearInputBuffer();
                
                if (cgpa < 0.0f || cgpa > 4.0f) {
                    cout << "[ERROR] Invalid CGPA! Must be between 0.0 and 4.0\n";
                } else {
                    sm.AddStudent(rollNo, name, dept, cgpa);
                    cout << "[SUCCESS] Student added successfully!\n";
                }
                pauseScreen();
                break;
            }
            
            case 2: {
                // Search by Roll Number
                int rollNo;
                cout << "\n--- Search Student by Roll Number ---\n";
                cout << "Enter Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                Student* student = sm.SearchByRollNo(rollNo);
                sm.PrintStudentInfo(student);
                pauseScreen();
                break;
            }
            
            case 3: {
                // Search by Name
                string name;
                cout << "\n--- Search Student by Name ---\n";
                cout << "Enter Student Name: ";
                getline(cin, name);
                
                Student* student = sm.SearchByName(name);
                sm.PrintStudentInfo(student);
                pauseScreen();
                break;
            }
            
            case 4: {
                // Update CGPA
                int rollNo;
                float newCGPA;
                
                cout << "\n--- Update Student CGPA ---\n";
                cout << "Enter Roll Number: ";
                cin >> rollNo;
                
                cout << "Enter New CGPA (0.0 - 4.0): ";
                cin >> newCGPA;
                clearInputBuffer();
                
                sm.UpdateCGPA(rollNo, newCGPA);
                pauseScreen();
                break;
            }
            
            case 5: {
                // Delete Student
                int rollNo;
                char confirm;
                
                cout << "\n--- Delete Student Record ---\n";
                cout << "Enter Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                // Show student info before deleting
                Student* student = sm.SearchByRollNo(rollNo);
                if (student != nullptr) {
                    sm.PrintStudentInfo(student);
                    cout << "\nAre you sure you want to delete this record? (y/n): ";
                    cin >> confirm;
                    clearInputBuffer();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        sm.DeleteStudent(rollNo);
                    } else {
                        cout << "[CANCELLED] Deletion cancelled.\n";
                    }
                }
                pauseScreen();
                break;
            }
            
            case 6: {
                // Display Student Info
                int rollNo;
                cout << "\n--- Display Student Information ---\n";
                cout << "Enter Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                Student* student = sm.SearchByRollNo(rollNo);
                sm.PrintStudentInfo(student);
                pauseScreen();
                break;
            }
            
            case 7: {
                // Display All Students
                cout << "\n--- All Students in System ---\n";
                sm.DisplayAllStudents();
                pauseScreen();
                break;
            }
            
            case 8: {
                // Sort Students by Roll Number
                cout << "\n--- Sort Students by Roll Number ---\n";
                
                cout << "\n[BEFORE SORTING]\n";
                sm.DisplayAllStudents();
                
                sm.BubbleSortByRollNo();
                
                cout << "\n[AFTER SORTING]\n";
                sm.DisplayAllStudents();
                
                pauseScreen();
                break;
            }
            
            case 9: {
                // Sort Students by CGPA (Selection Sort)
                cout << "\n--- Sort Students by CGPA (Highest to Lowest) ---\n";
                
                cout << "\n[BEFORE SORTING]\n";
                sm.DisplayAllStudents();
                
                sm.SelectionSortByCGPA();
                
                cout << "\n[AFTER SORTING]\n";
                sm.DisplayAllStudents();
                
                pauseScreen();
                break;
            }
            
            case 10:
                // Undo Student Action
                cout << "\n--- UNDO Student Action ---\n";
                sm.executeUndo();
                pauseScreen();
                break;
            
            case 11:
                // Redo Student Action
                cout << "\n--- REDO Student Action ---\n";
                sm.executeRedo();
                pauseScreen();
                break;
            
            case 12:
                backToMain = true;
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-12.\n";
                pauseScreen();
        }
    }
}

void handleCourseManagement(CourseManager& cm, StudentManager& sm) {
    int choice;
    bool backToMain = false;
    
    while (!backToMain) {
        cout << "\n==================================================\n";
        cout << "       COURSE REGISTRATION MANAGEMENT            \n";
        cout << "==================================================\n";
        cout << "1. Register Course for Student\n";
        cout << "2. Drop Course for Student\n";
        cout << "3. View Student's Registered Courses\n";
        cout << "--------------------------------------------------\n";
        cout << "4. [UNDO] Undo Last Course Action \n";
        cout << "5. [REDO] Redo Last Course Action \n";
        cout << "--------------------------------------------------\n";
        cout << "6. Back to Main Menu\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // Register Course
                int rollNo;
                string courseCode, courseName;
                
                cout << "\n--- Register Course for Student ---\n";
                cout << "Enter Student Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                // Verify student exists
                Student* student = sm.SearchByRollNo(rollNo);
                if (student == nullptr) {
                    cout << "[ERROR] Student not found!\n";
                    pauseScreen();
                    break;
                }
                
                cout << "Student Found: " << student->name << "\n";
                cout << "Enter Course Code: ";
                getline(cin, courseCode);
                
                cout << "Enter Course Name: ";
                getline(cin, courseName);
                
                cm.RegisterCourseForStudent(rollNo, courseCode, courseName);
                pauseScreen();
                break;
            }
            
            case 2: {
                // Drop Course
                int rollNo;
                string courseCode;
                
                cout << "\n--- Drop Course for Student ---\n";
                cout << "Enter Student Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                // Show current courses
                Student* student = sm.SearchByRollNo(rollNo);
                if (student == nullptr) {
                    cout << "[ERROR] Student not found!\n";
                    pauseScreen();
                    break;
                }
                
                cout << "Student: " << student->name << "\n";
                cout << "Current Courses:\n";
                cm.ViewStudentCourses(rollNo);
                
                cout << "\nEnter Course Code to Drop: ";
                getline(cin, courseCode);
                
                cm.DropCourse(rollNo, courseCode);
                pauseScreen();
                break;
            }
            
            case 3: {
                // View Courses
                int rollNo;
                
                cout << "\n--- View Student's Registered Courses ---\n";
                cout << "Enter Student Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                cm.ViewStudentCourses(rollNo);
                pauseScreen();
                break;
            }
            
            case 4:
                // Undo Course Action
                cout << "\n--- UNDO Course Action ---\n";
                cm.executeUndo();
                pauseScreen();
                break;
            
            case 5:
                // Redo Course Action
                cout << "\n--- REDO Course Action ---\n";
                cm.executeRedo();
                pauseScreen();
                break;
            
            case 6:
                backToMain = true;
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-6.\n";
                pauseScreen();
        }
    }
}

void handleCampusNavigation(CampusNavigator& cn) {
    int choice;
    bool backToMain = false;
    
    while (!backToMain) {
        cout << "\n==================================================\n";
        cout << "          CAMPUS NAVIGATION SYSTEM                \n";
        cout << "==================================================\n";
        cout << "Available Locations:\n";
        cout << "  - Gate_A\n";
        cout << "  - Admin_Block\n";
        cout << "  - CS_Department\n";
        cout << "  - Central_Library\n";
        cout << "  - Auditorium\n";
        cout << "  - Student_Cafeteria\n";
        cout << "--------------------------------------------------\n";
        cout << "1. Find Shortest Route\n";
        cout << "2. Back to Main Menu\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // Find Route
                string start, destination;
                
                cout << "\n--- Find Shortest Route ---\n";
                cout << "Enter Starting Location: ";
                getline(cin, start);
                
                cout << "Enter Destination: ";
                getline(cin, destination);
                
                cn.requestDirections(start, destination);
                pauseScreen();
                break;
            }
            
            case 2:
                backToMain = true;
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-2.\n";
                pauseScreen();
        }
    }
}

void handleLibraryManagement(LibraryManager& lm) {
    int choice;
    bool backToMain = false;
    
    while (!backToMain) {
        cout << "\n==================================================\n";
        cout << "          LIBRARY MANAGEMENT SYSTEM               \n";
        cout << "==================================================\n";
        cout << "1. Add New Book to Library\n";
        cout << "2. Issue Book to Student\n";
        cout << "3. Return Book\n";
        cout << "4. View Complete Library Catalog\n";
        cout << "5. Search Book by ID\n";
        cout << "6. Back to Main Menu\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // Add New Book
                int bookID;
                string title, author;
                
                cout << "\n--- Add New Book to Library ---\n";
                cout << "Enter Book ID: ";
                cin >> bookID;
                clearInputBuffer();
                
                cout << "Enter Book Title: ";
                getline(cin, title);
                
                cout << "Enter Author Name: ";
                getline(cin, author);
                
                lm.AddNewBook(bookID, title, author);
                cout << "[SUCCESS] Book '" << title << "' added to library catalog!\n";
                pauseScreen();
                break;
            }
            
            case 2: {
                // Issue Book
                int bookID;
                
                cout << "\n--- Issue Book to Student ---\n";
                cout << "Enter Book ID to Issue: ";
                cin >> bookID;
                clearInputBuffer();
                
                lm.IssueBook(bookID);
                pauseScreen();
                break;
            }
            
            case 3: {
                // Return Book
                int bookID;
                
                cout << "\n--- Return Book ---\n";
                cout << "Enter Book ID to Return: ";
                cin >> bookID;
                clearInputBuffer();
                
                lm.ReturnBook(bookID);
                pauseScreen();
                break;
            }
            
            case 4: {
                // View Catalog
                cout << "\n--- Library Catalog ---\n";
                lm.ViewLibraryCatalog();
                pauseScreen();
                break;
            }
            
            case 5: {
                // Search Book
                int bookID;
                
                cout << "\n--- Search Book by ID ---\n";
                cout << "Enter Book ID: ";
                cin >> bookID;
                clearInputBuffer();
                
                lm.SearchBook(bookID);
                pauseScreen();
                break;
            }
            
            case 6:
                backToMain = true;
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-6.\n";
                pauseScreen();
        }
    }
}

void handleComplaintTokenManagement(ComplaintManager& cpm) {
    int choice;
    bool backToMain = false;
    
    while (!backToMain) {
        cout << "\n==================================================\n";
        cout << "       COMPLAINT & TOKEN MANAGEMENT SYSTEM        \n";
        cout << "==================================================\n";
        cout << "       COMPLAINT SYSTEM (FIFO Queue)              \n";
        cout << "1. File New Complaint\n";
        cout << "2. Resolve Next Complaint\n";
        cout << "3. View Active Complaints\n";
        cout << "--------------------------------------------------\n";
        cout << "4. [UNDO] Undo Last Complaint Action \n";
        cout << "5. [REDO] Redo Last Complaint Action \n";
        cout << "--------------------------------------------------\n";
        cout << "       TOKEN SYSTEM (Circular Queue)              \n";
        cout << "6. Issue New Token\n";
        cout << "7. Serve Next Token\n";
        cout << "8. View Active Token Queue\n";
        cout << "--------------------------------------------------\n";
        cout << "9. Back to Main Menu\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // File Complaint
                int rollNo;
                string description;
                
                cout << "\n--- File New Complaint ---\n";
                cout << "Enter Your Roll Number: ";
                cin >> rollNo;
                clearInputBuffer();
                
                cout << "Enter Complaint Description: ";
                getline(cin, description);
                
                cpm.FileComplaint(rollNo, description);
                cout << "[SUCCESS] Your complaint has been registered!\n";
                cout << "[INFO] Complaints are resolved in FIFO order.\n";
                pauseScreen();
                break;
            }
            
            case 2: {
                // Resolve Complaint
                cout << "\n--- Resolve Next Complaint ---\n";
                cout << "[ACTION] Resolving the oldest complaint in queue...\n";
                cpm.resolveComplaint();
                pauseScreen();
                break;
            }
            
            case 3: {
                // View Active Complaints
                cout << "\n--- Active Complaints ---\n";
                cpm.viewActiceComplaints();
                pauseScreen();
                break;
            }
            
            case 4:
                // Undo Complaint Action
                cout << "\n--- UNDO Complaint Action ---\n";
                cpm.executeUndo();
                pauseScreen();
                break;
            
            case 5:
                // Redo Complaint Action
                cout << "\n--- REDO Complaint Action ---\n";
                cpm.executeRedo();
                pauseScreen();
                break;
            
            case 6: {
                // Issue Token
                cout << "\n--- Issue New Token ---\n";
                cout << "[ACTION] Generating token number...\n";
                cpm.IssueToken();
                cout << "[INFO] Please wait for your token number to be called.\n";
                pauseScreen();
                break;
            }
            
            case 7: {
                // Serve Token
                cout << "\n--- Serve Next Token ---\n";
                cout << "[ACTION] Calling next token from queue...\n";
                cpm.serveNextToken();
                pauseScreen();
                break;
            }
            
            case 8: {
                // View Token Queue
                cout << "\n--- Active Token Queue ---\n";
                cout << "[INFO] Tokens are served in FIFO order (First Come First Served)\n\n";
                cpm.ViewTokenQueue();
                pauseScreen();
                break;
            }
            
            case 9:
                backToMain = true;
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-9.\n";
                pauseScreen();
        }
    }
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}
