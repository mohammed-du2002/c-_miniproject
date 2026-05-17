#include "DepartmentService.h"
#include <iostream>

DepartmentService::DepartmentService(std::shared_ptr<IDepartmentDAO> deptDao)
    : departmentDAO(deptDao) {}

bool DepartmentService::addDepartment(const Department &dept)
{
    if (departmentDAO->nameExists(dept.name))
    {
        std::cerr << "Department name already exists: " << dept.name << std::endl;
        return false;
    }
    return departmentDAO->insert(dept);
}

bool DepartmentService::updateDepartment(const Department &dept)
{
    Department existing = departmentDAO->getById(dept.id);
    if (existing.id == -1)
    {
        std::cerr << "Department not found with ID: " << dept.id << std::endl;
        return false;
    }
    if (existing.name != dept.name && departmentDAO->nameExists(dept.name))
    {
        std::cerr << "Department name already exists: " << dept.name << std::endl;
        return false;
    }
    return departmentDAO->update(dept);
}

bool DepartmentService::removeDepartment(int id)
{
    Department existing = departmentDAO->getById(id);
    if (existing.id == -1)
    {
        std::cerr << "Department not found with ID: " << id << std::endl;
        return false;
    }
    return departmentDAO->deleteById(id);
}

Department DepartmentService::getDepartment(int id)
{
    return departmentDAO->getById(id);
}

std::vector<Department> DepartmentService::getAllDepartments()
{
    return departmentDAO->getAll();
}