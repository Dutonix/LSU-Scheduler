#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "dataclasses.hpp"
#include "preferences.hpp"
#include "datastore.hpp"
#include <algorithm>
#include <vector>


/**************************CLASS COURSE RECOMMENDATION ENGINE*****************************************/
/*
    The Course Recommendation Engine is responsible for generating recommendations based on the user's preference

*/

class CourseRecommendationEngine {
public:
    std::vector<CourseCatalog> recommendedCourses;

    CourseRecommendationEngine() {}
        // Helper function to add a new course to the recommended courses
    void addRecommendedCourse(CourseCatalog& course) {
        recommendedCourses.push_back(course);
    }

    bool isCourseNumberInDegreeData(const std::vector<DegreeAudit>& degreeData, int courseNumber) {
        for (const auto& audit : degreeData) {
            if (audit.getDegreeAuditNumber() == courseNumber) {
                return true;
            }
        }
        return false;
    }

    void updateDegreeData(std::vector<DegreeAudit>& degreeData, const std::vector<int>& completedCourses) {
        for (auto& audit : degreeData) {
            if (std::find(completedCourses.begin(), completedCourses.end(), audit.getDegreeAuditNumber()) != completedCourses.end()) {
                audit.markComplete(audit.getDegreeAuditNumber());
            }
        }
    }

    std::vector<DegreeAudit> filterIncompleteDegreeData( std::vector<DegreeAudit>& degreeData) {
        std::vector<DegreeAudit> remainingCourses;
        for (auto& audit : degreeData) {
            if (!audit.getDegreeAuditComplete()) {
                remainingCourses.push_back(audit);
            }
        }
        return remainingCourses;
    }

    std::vector<CourseCatalog> generateRecommendations(
        const std::vector<CourseCatalog>& catalog_Data,
        const std::vector<MetaData>& meta_Data,
        const std::vector<DegreeAudit>& degree_Data,
        const UserPreferences& userPreferences){

    // Step 1: Create a new vector of course numbers from the remaining degree audit data
    std::vector<int> remainingCourses;
    for (const auto& degreeCourse : degree_Data) {
        remainingCourses.push_back(degreeCourse.getDegreeAuditNumber());
    }
    
    // Step 2: Create a new vector of meta data objects from the remaining course numbers
    std::vector<MetaData> remainingMeta;
    for (const auto& metaCourse : meta_Data) {
        if (std::find(remainingCourses.begin(), remainingCourses.end(), metaCourse.getMetaCourseNumber()) != remainingCourses.end()) {
            remainingMeta.push_back(metaCourse);
        }
    }

    // Step 3: Remove meta data courses that are only available in the opposite semester
    // Rank the remainingMeta based on criteria

    // Step 4: Create a new vector of catalog data objects from the remaining course numbers
    std::vector<CourseCatalog> remainingCatalog;
    for (const auto& catalogCourse : catalog_Data) {
        if (std::find(remainingCourses.begin(), remainingCourses.end(), catalogCourse.getCourseNumber()) != remainingCourses.end()) {
            remainingCatalog.push_back(catalogCourse);
        }
    }
    // Step 5: Initialize variables
    int groupProjectCount = 0;
    int attendanceCount = 0;
    int labCount = 0;
    int labMax = userPreferences.get_userLabs();
    int workloadMax = userPreferences.get_userWorkload();
    // int attendanceMax = userPreferences.get_userAttendance();
    std::vector<int> recommendedCourses;

    std::cout << "\n\n";
    std::cout << "The Recommendation Engine is Running..." << std::endl;
    std::cout << "lab Maximum: " << labMax << std::endl;
    std::cout << "workload Maximum: " << workloadMax << std::endl;
    
    // Step 6: For each object in the remainingMeta vector
    for (const auto& metaCourse : remainingMeta) {

        auto completedCourse = std::find_if(degree_Data.begin(), degree_Data.end(), [metaCourse](const DegreeAudit& auditCourse) {
            return auditCourse.getDegreeAuditNumber() == metaCourse.getMetaCourseNumber() && auditCourse.getDegreeAuditComplete();
        });

        // If the course is already completed, skip it
        if (completedCourse != degree_Data.end()) {
            continue;
        }
        
        // Search the catalog data for the matching course number/s 
        for (const auto& catalogCourse : remainingCatalog) {

            // If the meta data course number matches the catalog course number
            // and if the course is not already in the recommendedCourses vector
            // and if the there are no time conflicts
            // deduct the workload value from the max workload value
            // and if the workload value is greater than or equal to 0 then add the course to the recommendedCourses vector
            if (metaCourse.getMetaCourseNumber() == catalogCourse.getCourseNumber()) {

                
                if (std::find(recommendedCourses.begin(), recommendedCourses.end(), catalogCourse.getCourseNumber()) == recommendedCourses.end()) {
                    
    
                //TODO: Check if the time slot is available
                    // Subtract the workload value from the max workload value
                    
                    // If after subtracting the workload value from the max workload value is less than or equal to 0
                    // break out of the loop
                
                    if (workloadMax >= 0) {
                        recommendedCourses.push_back(catalogCourse.getCourseNumber());
                        workloadMax -= metaCourse.getWorkload();

                        // Increment lab count
                        if (metaCourse.getLab()) {
                            labCount++;
                            std::cout << "Lab Count: " << labCount << std::endl;
                        }

                        // Increment counters for group projects and attendance
                        if (metaCourse.getGroupProject()) {
                            groupProjectCount++;
                            std::cout << "Group Project Count: " << groupProjectCount << std::endl;
                        }
                        if (metaCourse.getAttendance()) {
                            attendanceCount++;
                            std::cout << "Attendance Count: " << attendanceCount << std::endl;
                        }
                       // We don't need to check any more courses if the workload value is less than or equal to 0
                       // or the lab count is equal to the maximum
                       if (workloadMax <= 0 || labCount == labMax) {
                           break;
                       }
                    }
                } 
            } 
        }        
    }

    // Step 7: Return the recommendedCourses vector
    std::vector<CourseCatalog> recommendedCatalog;
    for (int courseNumber : recommendedCourses) {
        auto it = std::find_if(remainingCatalog.begin(), remainingCatalog.end(), [courseNumber](const CourseCatalog& catalogCourse) {
            return catalogCourse.getCourseNumber() == courseNumber;
        });
        if (it != remainingCatalog.end()) {
            recommendedCatalog.push_back(*it);
        }

    }
    return recommendedCatalog;
    }
    
};

#endif