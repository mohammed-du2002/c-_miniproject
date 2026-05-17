#include "EmployeeDAOSQLite.h"
#include "../entities/Employee.h"
#include <iostream>

EmployeeDAOSQLite::EmployeeDAOSQLite(const std::string& dbPath)
    : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

void EmployeeDAOSQLite::createTable() {
  db.exec(
      "CREATE TABLE IF NOT EXISTS employees ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "user_id INTEGER NOT NULL,"
      "department_id INTEGER,"
      "first_name TEXT NOT NULL,"
      "last_name TEXT NOT NULL,"
      "salary REAL NOT NULL,"
      "FOREIGN KEY(user_id) REFERENCES users(id),"
      "FOREIGN KEY(department_id) REFERENCES departments(id))");
}

bool EmployeeDAOSQLite::insert(const Employee& emp) {
  try {
    SQLite::Statement stmt(db,
                           "INSERT INTO employees (user_id, department_id, first_name, last_name, "
                           "salary) VALUES (?, ?, ?, ?, ?)");
    stmt.bind(1, emp.userId);
    stmt.bind(2, emp.departmentId > 0 ? emp.departmentId : SQLite::Null);
    stmt.bind(3, emp.firstName);
    stmt.bind(4, emp.lastName);
    stmt.bind(5, emp.salary);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error inserting employee: " << e.what() << std::endl;
    return false;
  }
}

Employee EmployeeDAOSQLite::getById(int id) {
  SQLite::Statement stmt(db,
                         "SELECT id, user_id, department_id, first_name, last_name, salary FROM "
                         "employees WHERE id = ?");
  stmt.bind(1, id);
  if (stmt.executeStep()) {
    Employee emp;
    emp.id = stmt.getColumn(0).getInt();
    emp.userId = stmt.getColumn(1).getInt();
    emp.departmentId = stmt.getColumn(2).isNull() ? -1 : stmt.getColumn(2).getInt();
    emp.firstName = stmt.getColumn(3).getText();
    emp.lastName = stmt.getColumn(4).getText();
    emp.salary = stmt.getColumn(5).getDouble();
    return emp;
  }
  return Employee();
}

std::vector<Employee> EmployeeDAOSQLite::getAll() {
  std::vector<Employee> employees;
  SQLite::Statement stmt(
      db, "SELECT id, user_id, department_id, first_name, last_name, salary FROM employees");
  while (stmt.executeStep()) {
    Employee emp;
    emp.id = stmt.getColumn(0).getInt();
    emp.userId = stmt.getColumn(1).getInt();
    emp.departmentId = stmt.getColumn(2).isNull() ? -1 : stmt.getColumn(2).getInt();
    emp.firstName = stmt.getColumn(3).getText();
    emp.lastName = stmt.getColumn(4).getText();
    emp.salary = stmt.getColumn(5).getDouble();
    employees.push_back(emp);
  }
  return employees;
}

bool EmployeeDAOSQLite::update(const Employee& emp) {
  try {
    SQLite::Statement stmt(db,
                           "UPDATE employees SET user_id = ?, department_id = ?, first_name = ?, "
                           "last_name = ?, salary = ? WHERE id = ?");
    stmt.bind(1, emp.userId);
    stmt.bind(2, emp.departmentId > 0 ? emp.departmentId : SQLite::Null);
    stmt.bind(3, emp.firstName);
    stmt.bind(4, emp.lastName);
    stmt.bind(5, emp.salary);
    stmt.bind(6, emp.id);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error updating employee: " << e.what() << std::endl;
    return false;
  }
}

bool EmployeeDAOSQLite::deleteById(int id) {
  try {
    SQLite::Statement stmt(db, "DELETE FROM employees WHERE id = ?");
    stmt.bind(1, id);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error deleting employee: " << e.what() << std::endl;
    return false;
  }
}

std::vector<Employee> EmployeeDAOSQLite::getByDepartmentId(int deptId) {
  std::vector<Employee> employees;
  SQLite::Statement stmt(db,
                         "SELECT id, user_id, department_id, first_name, last_name, salary FROM "
                         "employees WHERE department_id = ?");
  stmt.bind(1, deptId);
  while (stmt.executeStep()) {
    Employee emp;
    emp.id = stmt.getColumn(0).getInt();
    emp.userId = stmt.getColumn(1).getInt();
    emp.departmentId = stmt.getColumn(2).isNull() ? -1 : stmt.getColumn(2).getInt();
    emp.firstName = stmt.getColumn(3).getText();
    emp.lastName = stmt.getColumn(4).getText();
    emp.salary = stmt.getColumn(5).getDouble();
    employees.push_back(emp);
  }
  return employees;
}

Employee EmployeeDAOSQLite::getByUserId(int userId) {
  SQLite::Statement stmt(db,
                         "SELECT id, user_id, department_id, first_name, last_name, salary FROM "
                         "employees WHERE user_id = ?");
  stmt.bind(1, userId);
  if (stmt.executeStep()) {
    Employee emp;
    emp.id = stmt.getColumn(0).getInt();
    emp.userId = stmt.getColumn(1).getInt();
    emp.departmentId = stmt.getColumn(2).isNull() ? -1 : stmt.getColumn(2).getInt();
    emp.firstName = stmt.getColumn(3).getText();
    emp.lastName = stmt.getColumn(4).getText();
    emp.salary = stmt.getColumn(5).getDouble();
    return emp;
  }
  return Employee();
}