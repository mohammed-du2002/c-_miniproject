#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee
{
public:
    int id;
    int userId;
    int departmentId;
    std::string firstName;
    std::string lastName;
    double salary;

    Employee() : id(-1), userId(-1), departmentId(-1), salary(0.0) {}
    Employee(int uid, int deptId, const std::string &fname, const std::string &lname, double sal)
        : id(-1), userId(uid), departmentId(deptId), firstName(fname), lastName(lname), salary(sal) {}

    std::string getFullName() const
    {
        return firstName + " " + lastName;
    }
};

#endif