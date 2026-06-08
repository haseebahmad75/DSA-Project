#ifndef CAMPUS_NAVIGATOR_HPP
#define CAMPUS_NAVIGATOR_HPP

#include "../data_structures/CampusGraph.hpp"
#include <string>

class CampusNavigator {
private:
    CampusGraph campusMap;

public:
    CampusNavigator() {
        // Build out your structured university blueprint layout
        campusMap.addWalkway("Gate_A", "Admin_Block", 120);
        campusMap.addWalkway("Gate_A", "Central_Library", 300);
        campusMap.addWalkway("Admin_Block", "CS_Department", 80);
        campusMap.addWalkway("Admin_Block", "Auditorium", 150);
        campusMap.addWalkway("CS_Department", "Central_Library", 90);
        campusMap.addWalkway("Central_Library", "Student_Cafeteria", 110);
        campusMap.addWalkway("Auditorium", "Student_Cafeteria", 250);
    }

    void requestDirections(const string& start, const string& destination)
    {
        campusMap.calculateShortestRoute(start, destination);
    }
};

#endif