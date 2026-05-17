#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>

class Department
{
public:
    int id;
    std::string name;
    std::string description;

    Department() : id(-1), name(""), description("") {}
    Department(const std::string &n, const std::string &desc)
        : id(-1), name(n), description(desc) {}
};

#endif