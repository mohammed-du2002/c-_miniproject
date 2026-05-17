#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include "../dao/IEmployeeDAO.h"
#include "../dao/IDepartmentDAO.h"
#include "../entities/Employee.h"

#include <vector>
#include <memory>

class EmployeeService {
 public:
  EmployeeService(std::shared_ptr<IEmployeeDAO> empDao, std::shared_ptr<IDepartmentDAO> deptDao);
  bool addEmployee(const Employee& employee);
  bool updateEmployee(const Employee& employee);
  bool removeEmployee(int id);
  Employee getEmployee(int id);
  std::vector<Employee> getAllEmployees();
  std::vector<Employee> getEmployeesByDepartment(int departmentId);

 private:
  std::shared_ptr<IEmployeeDAO> employeeDAO;
  std::shared_ptr<IDepartmentDAO> departmentDAO;
};

#endif