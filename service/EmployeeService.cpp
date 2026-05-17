#include "EmployeeService.h"
#include <iostream>

EmployeeService::EmployeeService(std::shared_ptr<IEmployeeDAO> empDao,
                                 std::shared_ptr<IDepartmentDAO> deptDao)
    : employeeDAO(empDao), departmentDAO(deptDao) {}

bool EmployeeService::addEmployee(const Employee& employee) {
  if (employee.getFullName().empty()) {
    std::cerr << "Employee name cannot be empty." << std::endl;
    return false;
  }
  if (!departmentDAO->getById(employee.departmentId).name.empty()) {
    return employeeDAO->insert(employee);
  } else {
    std::cerr << "Department with ID " << employee.departmentId << " does not exist." << std::endl;
    return false;
  }
}

bool EmployeeService::updateEmployee(const Employee& employee) {
  if (employee.getFullName().empty()) {
    std::cerr << "Employee name cannot be empty." << std::endl;
    return false;
  }
  if (!departmentDAO->getById(employee.departmentId).name.empty()) {
    return employeeDAO->update(employee);
  } else {
    std::cerr << "Department with ID " << employee.departmentId << " does not exist." << std::endl;
    return false;
  }
}

bool EmployeeService::removeEmployee(int id) {
  return employeeDAO->deleteById(id);
}

Employee EmployeeService::getEmployee(int id) {
  return employeeDAO->getById(id);
}

std::vector<Employee> EmployeeService::getAllEmployees() {
  return employeeDAO->getAll();
}

std::vector<Employee> EmployeeService::getEmployeesByDepartment(int departmentId) {
  return employeeDAO->getByDepartmentId(departmentId);
}