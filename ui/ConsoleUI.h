#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <memory>
#include <string>

#include "service/AuthService.h"
class DepartmentService;
class EmployeeService;

class ConsoleUI {
 public:
  void run();

 private:
  void initializeDatabase();
  void createDefaultHR();
  AuthService::LoginResult promptLogin();

  void hrMenu(AuthService& authSvc, EmployeeService& empSvc, DepartmentService& deptSvc);

  /*Employee Management */
  void manageEmployees(AuthService& auth, EmployeeService& empSvc, DepartmentService& deptSvc);
  void listEmployees(EmployeeService& empSvc, DepartmentService& deptSvc);
  void addEmployee(AuthService& auth, EmployeeService& empSvc, DepartmentService& deptSvc);
  void editEmployee(EmployeeService& empSvc, DepartmentService& deptSvc);
  void deleteEmployee(EmployeeService& empSvc);

  /* Department Management */
  void manageDepartments(EmployeeService& empSvc, DepartmentService& deptSvc);
  void listDepartments(DepartmentService& deptSvc);
  void viewEmployeesByDepartment(EmployeeService& empSvc, DepartmentService& deptSvc);
  void addDepartment(DepartmentService& deptSvc);
  void editDepartment(DepartmentService& deptSvc);
  void deleteDepartment(DepartmentService& deptSvc);
};

#endif