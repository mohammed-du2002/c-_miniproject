#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <memory>
#include <string>

#include "service/AuthService.h"
class DepartmentService;
class EmployeeService;
class AttendanceService;

class ConsoleUI {
 public:
  void run();

 private:
  void initializeDatabase();
  void createDefaultHR();
  AuthService::LoginResult promptLogin();

  void hrMenu(AuthService& authSvc, EmployeeService& empSvc, DepartmentService& deptSvc,
              AttendanceService& attSvc);

  void employeeMenu(AuthService& authSvc, AttendanceService& attSvc,
                    AuthService::LoginResult loginResult);
  /*Employee Management */
  void manageEmployees(AuthService& auth, EmployeeService& empSvc, DepartmentService& deptSvc);
  void listEmployees(EmployeeService& empSvc, DepartmentService& deptSvc);
  void addEmployee(AuthService& auth, EmployeeService& empSvc, DepartmentService& deptSvc);
  void editEmployee(EmployeeService& empSvc, DepartmentService& deptSvc);
  void deleteEmployee(EmployeeService& empSvc);

  /* Attendance Management */
  void manageAttendance(EmployeeService& empSvc, AttendanceService& attSvc);
  void viewAttendanceReports(AttendanceService& attSvc, EmployeeService& empSvc);
  void viewAttendanceByDateRange(EmployeeService& empSvc, AttendanceService& attSvc);
  void markAbsent(AttendanceService& attSvc, EmployeeService& empSvc);
  void clockIn(AttendanceService& attSvc, int employeeId);
  void clockOut(AttendanceService& attSvc, int employeeId);
  void viewMyAttendance(AttendanceService& attSvc, int employeeId);

  /* Department Management */
  void manageDepartments(EmployeeService& empSvc, DepartmentService& deptSvc);
  void listDepartments(DepartmentService& deptSvc);
  void viewEmployeesByDepartment(EmployeeService& empSvc, DepartmentService& deptSvc);
  void addDepartment(DepartmentService& deptSvc);
  void editDepartment(DepartmentService& deptSvc);
  void deleteDepartment(DepartmentService& deptSvc);

  /* Attendance Management */
};

#endif