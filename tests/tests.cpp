#include "../include/catch.hpp"
#include "../include/engine.hpp"
#include "../include/datastore.hpp"
#include "../include/preferences.hpp"
#include "../include/dataclasses.hpp"

#include <iostream>
#include "python2.7/python.h"


PROVIDED_TEST("Test CourseRecommendationEngine") {
    // Create a DataStore object and load data
    DataStore store;

     //Converts the JSON files from data/databases (CatalogData, MetaData, and DegreeAudit) 
     //to a vector of CourseCatalog, MetaData, and DegreeAudit objects 
     //and stores them in the DataStore object
     //so store is an object of type DataStore
     //and it contains the vector of CourseCatalog, MetaData, and DegreeAudit objects
     //the vector looks like a list of objects
    store.load_all_Data(); 

    // Set user preferences
    UserPreferences preferences;
    preferences.set_User("John");
    preferences.set_userWorkload(30);
    preferences.set_userAttendance(3);
    preferences.set_userGroupProjects(3);
    preferences.set_completedCourses({4360, 4402, 4444, 2262, 2362, 2463, 2610, 3102});

    // Create a CourseRecommendationEngine object
    CourseRecommendationEngine engine; 

    // Generate recommendations
    std::vector<CourseCatalog> recommendations = engine.generateRecommendations(
        store.get_CatalogData(),
        store.get_MetaData(),
        store.get_DegreeData(),
        preferences
    );

    // Print recommended courses
    std::cout << "\n\n" << "Recommended Courses: \n";
    for (const auto& course : recommendations) {
        std::cout << course << "\n";
    }
}


// PROVIDED_TEST("Test function call to generatedata") {
//     PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pResult;
//     Py_Initialize();
//     //build name object
//     pName = PyString_FromString((char*)"generatedata");
//     //load module object
//     pModule = PyImport_Import(pName);
//     pDict = PyModule_GetDict(pModule);
// }