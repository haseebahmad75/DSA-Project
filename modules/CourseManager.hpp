#ifndef COURSE_MANAGER_HPP
#define COURSE_MANAGER_HPP

#include"StudentManager.hpp"
#include"../data_structures/GenericStack.hpp"
#include<iostream>
#include<string>
using namespace std;

struct CourseAction
{
    string type;
    int stuRollNo;
    string courseName;
    string courseCode;
};

class CourseManager
{
    private:
    StudentManager & sm; // reference to the student's data

    GenericStack<CourseAction> undoStack;
    GenericStack<CourseAction> redoStack;

    public:
    CourseManager(StudentManager & manager) : sm(manager) {}
    
    // Register a course to a specific student
    void RegisterCourseForStudent(int rollNo, string code, string name)
    {
        Student * stu = sm.SearchByRollNo(rollNo);

        if(stu == NULL)
        {
            cout<<"Registration Error: Cannot find student with Roll No: " <<rollNo <<"\n";
            return;
        }

        stu->registeredCourses.AddCourse(code,name);
        cout<<"Success: " <<stu->name <<" registered for " <<name <<"\n";

        CourseAction action = {"Register",rollNo, name, code};
        undoStack.push(action);

        redoStack.clear();
        
    }

    // Drop a course for a specific student
    void DropCourse(int rollNo, string code)
    {
        Student * stu = sm.SearchByRollNo(rollNo);

        if(stu == NULL)
        {
            cout<<"Drop Error: Cannot find student with Roll No: " <<rollNo <<"\n";
            return;
        }

        // we need courseName before dropping
        string name = "";
        Node * temp = stu->registeredCourses.head;
        while(temp != NULL)
        {
            if(temp->courseCode == code)
            {
                name = temp->courseName;
                break;
            }
            temp = temp->next;
        }

        if(stu->registeredCourses.DropCourse(code))
        {
            cout<<"Success: Dropped course " <<code <<" for " <<stu->name <<"\n";

            // writing it inside if block, so it doesn't record failed drops

            CourseAction action = {"Drop", rollNo, name, code};
            undoStack.push(action);

            redoStack.clear();
        }
        else
        {
            cout<<"Drop Error: Course " <<code <<" was not found in " <<stu->name <<"'s record \n";
        }

    }

    void executeUndo()
    {
        if(undoStack.isEmpty())
        {
            cout<<"[Undo Alert] : No course left to revert\n";
            return;
        }

        CourseAction lastAction = undoStack.pop();
        redoStack.push(lastAction);

        if(lastAction.type == "Register") // if last action was Register, then we need to remove it to undo it
        {
            Student * stu = sm.SearchByRollNo(lastAction.stuRollNo);
            if(stu != NULL)
            {
                stu->registeredCourses.DropCourse(lastAction.courseCode);
                cout<<"[Undo Action] : Removed course " <<lastAction.courseName <<" from Roll No " <<lastAction.stuRollNo;
            }
        }
        else if(lastAction.type == "Drop")
        {
            Student * stu = sm.SearchByRollNo(lastAction.stuRollNo);
            if(stu != NULL)
            {
                stu->registeredCourses.AddCourse(lastAction.courseCode, lastAction.courseName);
                cout<<"[Undo Action]: Re-addded course" <<lastAction.courseName <<" to Roll No" <<lastAction.stuRollNo <<"\n";
            }
        }
    }

    void executeRedo()
    {
        if(redoStack.isEmpty())
        {
            cout<<"[Redo System] Alert: Already at the latest action state\n ";
            return;
        }

         
        CourseAction actionToRedo = redoStack.pop();
        undoStack.push(actionToRedo);

        if(actionToRedo.type == "Register")
        {
            Student * stu = sm.SearchByRollNo(actionToRedo.stuRollNo);
            if(stu != NULL)
            {
                stu->registeredCourses.AddCourse(actionToRedo.courseCode, actionToRedo.courseName);
                cout<<"[Redo Action] : Re-enrolled Roll No " <<actionToRedo.stuRollNo <<" into course " <<actionToRedo.courseName <<"\n";
            }
        }
        else if(actionToRedo.type == "Drop")
        {
            Student * stu = sm.SearchByRollNo(actionToRedo.stuRollNo);
            if(stu != NULL)
            {
                stu->registeredCourses.DropCourse(actionToRedo.courseCode);
                cout<<"[Redo Action] :  Re-dropped Roll No " <<actionToRedo.stuRollNo <<" form course " <<actionToRedo.courseName <<"\n";
            }
        }
    }

    void ViewStudentCourses(int rollNo)
    {
        Student * stu = sm.SearchByRollNo(rollNo);
        if(stu == NULL)
        {
            cout<<"Error: Cannot find student with Roll No " << rollNo << "\n";
            return;
        }
        cout << "\n--- Courses for " <<stu->name <<" (Roll No: " << rollNo << ") ---\n";
        stu->registeredCourses.Display();
    }
};

#endif