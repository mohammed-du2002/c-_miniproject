#include "ConsoleUI.h"
#include "../service/DepartmentService.h"
#include "../service/AuthService.h"
#include "../service/EmployeeService.h"
#include "../dao/UserDAOSQLite.h"
#include "../dao/EmployeeDAOSQLite.h"
#include "../dao/DepartmentDAOSQLite.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::run() {
  initializeDatabase();
  createDefaultHR();

  auto userDAO = std::make_shared<UserDAOSQLite>("hr.db");
  auto empDAO = std::make_shared<EmployeeDAOSQLite>("hr.db");
  auto deptDAO = std::make_shared<DepartmentDAOSQLite>("hr.db");

  AuthService authService(userDAO, empDAO);
  EmployeeService empService(empDAO, deptDAO);
  DepartmentService deptService(deptDAO);
  while (true) {
    auto result = promptLogin();
    if (!result.success) {
      std::cout << "Login failed. Goodbye!\n";
      break;
    }

    std::cout << "\nWelcome! Logged in as " << result.role << ".\n";

    if (result.role == "HR") {
      hrMenu(authService, empService, deptService);
    } else {
    }

    std::cout << "Logged out successfully.\n";
  }
}

void ConsoleUI::initializeDatabase() {
  auto deptDAO = std::make_shared<DepartmentDAOSQLite>("hr.db");
  auto empDAO = std::make_shared<EmployeeDAOSQLite>("hr.db");
  auto userDAO = std::make_shared<UserDAOSQLite>("hr.db");

  deptDAO->createTable();
  empDAO->createTable();
  userDAO->createTable();
}

void ConsoleUI::hrMenu(AuthService& authSvc, EmployeeService& empSvc, DepartmentService& deptSvc) {
  int choice;
  do {
    std::cout << "\n--- HR Management ---\n";
    std::cout << "1. Manage Departments\n";
    std::cout << "2. Manage Employees\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        manageDepartments(empSvc, deptSvc);
        break;
      case 2:
        manageEmployees(authSvc, empSvc, deptSvc);
        break;
      case 3:
        return;
      default:
        std::cout << "Invalid choice.\n";
    }
  } while (true);
}

/*Auth Service*/
AuthService::LoginResult ConsoleUI::promptLogin() {
  AuthService::LoginResult result;
  result.success = false;

  auto userDAO = std::make_shared<UserDAOSQLite>("hr.db");
  auto empDAO = std::make_shared<EmployeeDAOSQLite>("hr.db");
  AuthService auth(userDAO, empDAO);

  std::string username, password;
  std::cout << "\n=== HR System Login ===\n";
  std::cout << "Username: ";
  std::cin >> username;
  std::cout << "Password: ";
  std::cin >> password;

  return auth.login(username, password);
}

/*Manage Employees*/
void ConsoleUI::manageEmployees(AuthService& auth, EmployeeService& empSvc,
                                DepartmentService& deptSvc) {
  int choice;
  do {
    std::cout << "\n--- Manage Employees ---\n";
    std::cout << "1. List Employees\n";
    std::cout << "2. Add Employee\n";
    std::cout << "3. Edit Employee\n";
    std::cout << "4. Delete Employee\n";
    std::cout << "5. Back\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        listEmployees(empSvc, deptSvc);
        break;
      case 2:
        addEmployee(auth, empSvc, deptSvc);
        break;
      case 3:
        editEmployee(empSvc, deptSvc);
        break;
      case 4:
        deleteEmployee(empSvc);
        break;
      case 5:
        return;
      default:
        std::cout << "Invalid choice.\n";
    }
  } while (true);
}

void ConsoleUI::listEmployees(EmployeeService& empSvc, DepartmentService& deptSvc) {
  auto emps = empSvc.getAllEmployees();
  if (emps.empty()) {
    std::cout << "No employees found.\n";
    return;
  }
  std::cout << "\n=== Employees ===\n";
  std::cout << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(20) << "Department\n";
  std::cout << std::string(45, '-') << "\n";
  for (const auto& e : emps) {
    Department dept = deptSvc.getDepartment(e.departmentId);
    std::cout << std::setw(5) << e.id << std::setw(20) << e.getFullName() << std::setw(20)
              << dept.name << "\n";
  }
}

void ConsoleUI::addEmployee(AuthService& auth, EmployeeService& empSvc,
                            DepartmentService& deptSvc) {
  std::string firstName, lastName, username, password;
  double salary;
  int deptId;

  std::cout << "First Name: ";
  std::cin >> firstName;
  std::cout << "Last Name: ";
  std::cin >> lastName;
  std::cout << "Username: ";
  std::cin >> username;
  std::cout << "Password: ";
  std::cin >> password;
  std::cout << "Salary: ";
  std::cin >> salary;
  std::cout << "Department ID (-1 for none): ";
  std::cin >> deptId;

  // Create user first
  if (!auth.createUser(username, password, "Employee")) {
    std::cout << "Failed to create user. Username may already exist.\n";
    return;
  }

  // Get the created user to get the ID
  auto userDAO = std::make_shared<UserDAOSQLite>("hr.db");
  User user = userDAO->getByUsername(username);
  if (user.id == -1) {
    std::cout << "Failed to retrieve created user.\n";
    return;
  }

  // Create employee with the user ID
  Employee emp(user.id, deptId, firstName, lastName, salary);
  if (empSvc.addEmployee(emp)) {
    std::cout << "Employee added successfully with user account.\n";
  } else {
    std::cout << "Failed to add employee.\n";
  }
}

void ConsoleUI::editEmployee(EmployeeService& empSvc, DepartmentService& deptSvc) {
  int id;
  std::cout << "Enter Employee ID to edit: ";
  std::cin >> id;

  Employee emp = empSvc.getEmployee(id);
  if (emp.id == -1) {
    std::cout << "Employee not found.\n";
    return;
  }

  std::string fname, lname;
  int deptId;
  double salary;

  std::cout << "Current: " << emp.getFullName() << ", Dept ID: " << emp.departmentId
            << ", Salary: " << emp.salary << "\n";
  std::cout << "New First Name (leave empty to keep): ";
  std::cin >> fname;
  std::cout << "New Last Name (leave empty to keep): ";
  std::cin >> lname;
  std::cout << "New Department ID (0 to keep): ";
  std::cin >> deptId;
  std::cout << "New Salary (0 to keep): ";
  std::cin >> salary;

  if (!fname.empty()) emp.firstName = fname;
  if (!lname.empty()) emp.lastName = lname;
  if (deptId != 0) emp.departmentId = deptId;
  if (salary != 0) emp.salary = salary;

  if (empSvc.updateEmployee(emp)) {
    std::cout << "Employee updated successfully.\n";
  }
}

void ConsoleUI::deleteEmployee(EmployeeService& empSvc) {
  int id;
  std::cout << "Enter Employee ID to delete: ";
  std::cin >> id;

  if (empSvc.removeEmployee(id)) {
    std::cout << "Employee deleted successfully.\n";
  } else {
    std::cout << "Failed to delete employee.\n";
  }
}

void ConsoleUI::createDefaultHR() {
  auto userDAO = std::make_shared<UserDAOSQLite>("hr.db");
  if (!userDAO->usernameExists("hr")) {
    User hrUser;
    hrUser.username = "hr";
    hrUser.passwordHash = "hr";  // In production, use a secure hash
    hrUser.role = "HR";
    userDAO->insert(hrUser);
  }
}

/*Manage Departments*/
void ConsoleUI::manageDepartments(EmployeeService& empSvc, DepartmentService& deptSvc) {
  int choice;
  do {
    std::cout << "\n--- Manage Departments ---\n";
    std::cout << "1. List Departments\n";
    std::cout << "2. View Employees in Department\n";
    std::cout << "3. Add Department\n";
    std::cout << "4. Edit Department\n";
    std::cout << "5. Delete Department\n";
    std::cout << "6. Back\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        listDepartments(deptSvc);
        break;
      case 2:
        viewEmployeesByDepartment(empSvc, deptSvc);
        break;
      case 3:
        addDepartment(deptSvc);
        break;
      case 4:
        editDepartment(deptSvc);
        break;
      case 5:
        deleteDepartment(deptSvc);
        break;
      case 6:
        return;
      default:
        std::cout << "Invalid choice.\n";
    }
  } while (true);
}

void ConsoleUI::listDepartments(DepartmentService& deptSvc) {
  auto depts = deptSvc.getAllDepartments();
  if (depts.empty()) {
    std::cout << "No departments found.\n";
    return;
  }
  std::cout << "\n=== Departments ===\n";
  std::cout << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(30) << "Description\n";
  std::cout << std::string(55, '-') << "\n";
  for (const auto& d : depts) {
    std::cout << std::setw(5) << d.id << std::setw(20) << d.name << std::setw(30) << d.description
              << "\n";
  }
}

void ConsoleUI::viewEmployeesByDepartment(EmployeeService& empSvc, DepartmentService& deptSvc) {
  int deptId;
  std::cout << "Enter Department ID: ";
  std::cin >> deptId;

  Department dept = deptSvc.getDepartment(deptId);
  if (dept.id == -1) {
    std::cout << "Department not found.\n";
    return;
  }

  auto employees = empSvc.getEmployeesByDepartment(deptId);
  if (employees.empty()) {
    std::cout << "No employees found in department '" << dept.name << "'.\n";
    return;
  }

  std::cout << "\nEmployees in department '" << dept.name << "':\n";
  std::cout << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(10) << "Salary" << "\n";
  std::cout << std::string(40, '-') << "\n";
  for (const auto& emp : employees) {
    std::cout << std::setw(5) << emp.id << std::setw(20) << emp.getFullName() << std::setw(10)
              << emp.salary << "\n";
  }
}

void ConsoleUI::addDepartment(DepartmentService& deptSvc) {
  std::string name, desc;
  std::cout << "Department Name: ";
  std::cin >> name;
  std::cout << "Description: ";
  std::cin >> desc;

  Department dept(name, desc);
  if (deptSvc.addDepartment(dept)) {
    std::cout << "Department added successfully.\n";
  }
}

void ConsoleUI::editDepartment(DepartmentService& deptSvc) {
  int id;
  std::cout << "Enter Department ID to edit: ";
  std::cin >> id;

  Department dept = deptSvc.getDepartment(id);
  if (dept.id == -1) {
    std::cout << "Department not found.\n";
    return;
  }

  std::string name, desc;
  std::cout << "Current: " << dept.name << " - " << dept.description << "\n";
  std::cout << "New Name (leave empty to keep): ";
  std::cin >> name;
  std::cout << "New Description (leave empty to keep): ";
  std::cin >> desc;

  if (!name.empty()) dept.name = name;
  if (!desc.empty()) dept.description = desc;

  if (deptSvc.updateDepartment(dept)) {
    std::cout << "Department updated successfully.\n";
  }
}

void ConsoleUI::deleteDepartment(DepartmentService& deptSvc) {
  int id;
  std::cout << "Enter Department ID to delete: ";
  std::cin >> id;

  if (deptSvc.removeDepartment(id)) {
    std::cout << "Department deleted successfully.\n";
  } else {
    std::cout << "Failed to delete department.\n";
  }
}
