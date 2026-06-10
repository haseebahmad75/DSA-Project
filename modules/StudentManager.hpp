#pragma once
#include"../data_structures/DynamicArray.hpp"
#include"../data_structures/GenericStack.hpp"
#include"../utils/FileManager.hpp"
#include"../models/Student.hpp"
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

};