#ifndef PREFERENCES_HPP
#define PREFERENCES_HPP

#include <string>
#include <vector>




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASS USER PREFERENCES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// User preferences or criteria will be stored in this class and passed to the CourseRecommendationEngine
// When the user inputs their preferences, they will be stored in this class 
// Preferences include: workload threshold, # of classes with a group project, # of classes with attendance being part of the grade
class UserPreferences {
    std::string user;
    std::vector<int> completed_courses;
    int max_labs;
    int max_workload; 
    int num_of_group_projects; 
    int attendance_part_of_grade;
public:
	// Default constructor
    UserPreferences() {}
    
    UserPreferences(
        std::string user,
        std::vector<int> completed_courses,
        int max_labs,
        int max_workload, 
        int num_of_group_projects, 
        int attendance_part_of_grade)
        : user(user), 
        completed_courses(completed_courses), 
        max_labs(max_labs),
        max_workload(max_workload), 
        num_of_group_projects(num_of_group_projects), 
        attendance_part_of_grade(attendance_part_of_grade) {}

    UserPreferences getUserPreferences() {
        return UserPreferences(user, completed_courses, max_labs, max_workload, num_of_group_projects, attendance_part_of_grade);}

    std::string get_User() {return user;}
    std::vector<int> get_completedCourses() const {return completed_courses;};
    int get_userLabs() const {return max_labs;}
    int get_userWorkload() const {return max_workload;}
    int get_userGroupProjects() const {return num_of_group_projects;}
    int get_userAttendance() const {return attendance_part_of_grade;}

    void set_User(const std::string& user) {this->user = user;}
    void set_userLabs(int max_labs) {this->max_labs = max_labs;}
    void set_completedCourses(const std::vector<int>& completed_courses) {this->completed_courses = completed_courses;}
    void set_userWorkload(int max_workload) {this->max_workload = max_workload;}
    void set_userGroupProjects(int num_of_group_projects) {this->num_of_group_projects = num_of_group_projects;}
    void set_userAttendance(int attendance_part_of_grade) {this->attendance_part_of_grade = attendance_part_of_grade;}

};

#endif