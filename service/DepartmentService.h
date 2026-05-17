#ifndef DEPARTMENT_SERVICE_H
#define DEPARTMENT_SERVICE_H

#include "../dao/IDepartmentDAO.h"
#include "../entities/Department.h"
#include <vector>
#include <memory>

class DepartmentService
{
public:
    DepartmentService(std::shared_ptr<IDepartmentDAO> deptDao);
    bool addDepartment(const Department &dept);
    bool updateDepartment(const Department &dept);
    bool removeDepartment(int id);
    Department getDepartment(int id);
    std::vector<Department> getAllDepartments();

private:
    std::shared_ptr<IDepartmentDAO> departmentDAO;
};

#endif