#pragma once
#include"../data_structures/DynamicArray.hpp"
#include"../data_structures/GenericStack.hpp"
#include"../utils/FileManager.hpp"
#include"../models/Student.hpp"
#include<iomanip>
using namespace std;

// unique payload struct that will be used as snapshot state
struct StudentAction
{
    string type;
    int rollNo;
    string name;
    string department;
    float cgpa;
};
class StudentManager
{
    private:
    DynamicArray<Student> studentRecords;
    const string fileName = "D:/Smart University System/students.txt";

    GenericStack<StudentAction> undoStack;
    GenericStack<StudentAction> redoStack;

    public:
    void InitSystem()
    {
        FileManager::LoadStudents(fileName,studentRecords);
    }

    void AddStudent(int rollNo, string name, string dept, float cgpa)
    {
        cout << "Adding student: " << rollNo << " - " << name << "\n";
        Student s = {rollNo,name,dept,cgpa};
        studentRecords.push_back(s);
        cout << "Student successfully added to records\n";

        // Log a snapshot payload onto the undo history tracker
        StudentAction action = {"ADD",rollNo, name, dept, cgpa};
        undoStack.push(action);

        redoStack.clear();
    }

    void executeUndo()
    {
        if(undoStack.isEmpty())
        {
            cout<<"[Undo System] Alert: No student record left to revert\n";
            return;
        }

        // stores the action in lastAction by popping it from undoStack, that was storing all the added students
        StudentAction lastAction = undoStack.pop();
        
        // pushing it in redoStack, if the user wants to do redo after undo
        redoStack.push(lastAction);

        if(lastAction.type == "ADD") // this ADD ensures whether the student was added or not
        {
            // Delete from memory (studentRecords array)
            int targetIndex = -1;
            for(int i = 0; i < studentRecords.getSize(); i++)
            {
                if(studentRecords.get(i).rollNo == lastAction.rollNo)
                {
                    targetIndex = i;
                    break;
                }
            }
            
            if(targetIndex != -1)
            {
                studentRecords.removeAt(targetIndex);
            }

            // Delete from file
            FileManager::DeleteStudentFromFile(fileName, lastAction.rollNo);

            cout << "[Undo Action] Successfully deleted mistakenly added Student Roll No: " << lastAction.rollNo << "\n";
        }
    }

    // redoing the previously undone step
    void executeRedo()
    {
        if(redoStack.isEmpty())
        {
            cout<<"[Redo Alert]: Already at the latest action state\n";
            return;
        }

        StudentAction actionToRedo = redoStack.pop();
        // push it back on the active undo stack
        undoStack.push(actionToRedo);

        if(actionToRedo.type == "ADD")
        {
            // Re-add the student to memory
            Student s(actionToRedo.rollNo, actionToRedo.name, actionToRedo.department, actionToRedo.cgpa);
            studentRecords.push_back(s);

            // Re-add to file by saving the entire state
            FileManager::SaveStudents(fileName, studentRecords);

            cout << "[Redo Action] Re-inserted Student Roll No: " << actionToRedo.rollNo << " back into the database.\n";
        }
    }

    void SaveSystemState()
    {
        FileManager::SaveStudents(fileName, studentRecords);
    }

    // linear search implemented
    Student* SearchByRollNo(int rollNo) // returns the address of that student
    {
        for(int i = 0; i < studentRecords.getSize(); i++)
        {
            if(studentRecords.get(i).rollNo == rollNo)
            {
                return &(studentRecords.get(i));
            }
        }
        return nullptr;
    }

    Student * SearchByName(string name)
    {
        for(int i = 0; i < studentRecords.getSize(); i++)
        {
            if(studentRecords.get(i).name == name)
            {
                return &(studentRecords.get(i));
            }
        }
        return nullptr;
    }

    void UpdateCGPA(int rollNo, float nCGPA)
    {
        Student * ptr = SearchByRollNo(rollNo);

        if(ptr == NULL)
        {
            cout<<"Error: Student with " <<rollNo <<" not found!\n"; 
            return;
        }

        if(nCGPA < 0.0f || nCGPA > 4.0f)
        {
            cout<<"Update Error: Invalid CGPA value.\n";
            return;
        }

        ptr->cgpa = nCGPA;
        cout<<"Success: CGPA for " <<ptr->name <<" updated to " <<nCGPA <<".\n";

    }

    void DeleteStudent(int rollNo)
    {
        int targetIndex = -1;

        for(int i = 0; i < studentRecords.getSize(); i++) // gets the index number of where the student with that rollNo is stored
        {
            if(studentRecords.get(i).rollNo == rollNo)
            {
                targetIndex = i;
                break;
            }
        }

        if(targetIndex == -1)
        {
            cout<<"Error: Student with Roll No " <<rollNo <<" not found!\n";
            return;
        }
 
        studentRecords.removeAt(targetIndex);
        cout<<"Success: Student with Roll No " <<rollNo <<" has been deleted!\n";
    }

    void PrintStudentInfo(Student* ptr)
    {
        if(ptr == NULL)
        {
            cout<<"Error! Student record not found!\n";
            return;
        }

        cout<<"\n===================================";
        cout<<"\nRoll Number: " <<ptr->rollNo;
        cout<<"\nName: " <<ptr->name;
        cout<<"\nDepartment: " <<ptr->department;
        cout<<"\nCGPA: " <<ptr->cgpa;
        cout<<"\n===================================\n";
    }

    void DisplayAllStudents()
    {
        if(studentRecords.getSize() == 0)
        {
            cout<<"No students in the system.\n";
            return;
        }

        cout<<"\n==================================================\n";
        cout<<"           ALL STUDENTS IN SYSTEM                 \n";
        cout<<"==================================================\n";
        cout<<"Roll No | Name                | Department          | CGPA\n";
        cout<<"--------------------------------------------------\n";

        for(int i = 0; i < studentRecords.getSize(); i++)
        {
            Student& s = studentRecords.get(i);
            cout.width(7);
            cout<<left<<s.rollNo<<" | ";
            
            cout.width(19);
            cout<<left<<s.name<<" | ";
            
            cout.width(19);
            cout<<left<<s.department<<" | ";
            
            cout<<fixed;
            cout.precision(2);
            cout<<s.cgpa<<"\n";
        }
        cout<<"==================================================\n";
    }

    void BubbleSortByRollNo()
    {
        int n = studentRecords.getSize();
        
        if(n <= 1)
        {
            cout<<"\n[INFO] Not enough students to sort (need at least 2).\n";
            return;
        }

        // Bubble Sort Algorithm
        for(int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            
            for(int j = 0; j < n - i - 1; j++)
            {   
                if(studentRecords.get(j).rollNo > studentRecords.get(j + 1).rollNo)
                {
                    // Swap students
                    Student temp = studentRecords.get(j);
                    studentRecords.get(j) = studentRecords.get(j + 1);
                    studentRecords.get(j + 1) = temp;
                    
                    swapped = true;
                }
            }
            
            // Optimization: if no swaps in this pass, array is sorted
            if(!swapped)
            {
                cout<<"[OPTIMIZATION] Early termination at pass "<<(i+1)<<" - Array already sorted!\n";
                break;
            }
        }
    }

    void SelectionSortByCGPA()
    {
        int n = studentRecords.getSize();
        
        if(n <= 1)
        {
            cout<<"\n[INFO] Not enough students to sort (need at least 2).\n";
            return;
        }
        
        // Selection Sort Algorithm (Descending order - highest CGPA first)
        for(int i = 0; i < n - 1; i++)
        {
            int maxIndex = i;
            
            for(int j = i + 1; j < n; j++)
            {   
                // Find maximum CGPA (descending order)
                if(studentRecords.get(j).cgpa > studentRecords.get(maxIndex).cgpa)
                {
                    maxIndex = j;
                }
            }
            
            // Swap if maximum is not at current position
            if(maxIndex != i)
            {
                Student temp = studentRecords.get(i);
                studentRecords.get(i) = studentRecords.get(maxIndex);
                studentRecords.get(maxIndex) = temp;
            }
        }

        cout<<"[INFO] Students sorted from HIGHEST to LOWEST CGPA\n";
    }

};