#ifndef STUDENT_H
#define STUDENT_H
#include <string>
struct Student {
    int id;
    std::string name;
    int year_of_enrollment;
    float gpa;
    Student(int id, const std::string& name, int year, float gpa)
        : id(id), name(name), year_of_enrollment(year), gpa(gpa) {}
};
#endif // STUDENT_H