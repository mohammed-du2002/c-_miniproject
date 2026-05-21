#include "DepartmentDAOSQLite.h"
#include "../entities/Department.h"
#include <iostream>

DepartmentDAOSQLite::DepartmentDAOSQLite(const std::string& dbPath)
    : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

DepartmentDAOSQLite::~DepartmentDAOSQLite() = default;

void DepartmentDAOSQLite::createTable() {
  db.exec(
      "CREATE TABLE IF NOT EXISTS departments ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "name TEXT NOT NULL UNIQUE,"
      "description TEXT)");
}

bool DepartmentDAOSQLite::insert(const Department& dept) {
  try {
    SQLite::Statement query(db, "INSERT INTO departments (name, description) VALUES (?, ?)");
    query.bind(1, dept.name);
    query.bind(2, dept.description);
    query.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Insert error: " << e.what() << std::endl;
    return false;
  }
}

Department DepartmentDAOSQLite::getById(int id) {
  SQLite::Statement stmt(db, "SELECT id, name, description FROM departments WHERE id = ?");
  stmt.bind(1, id);
  if (stmt.executeStep()) {
    Department dept;
    dept.id = stmt.getColumn(0).getInt();
    dept.name = stmt.getColumn(1).getText();
    dept.description = stmt.getColumn(2).isNull() ? "" : stmt.getColumn(2).getText();
    return dept;
  }
  return Department();
}

std::vector<Department> DepartmentDAOSQLite::getAll() {
  std::vector<Department> departments;
  SQLite::Statement stmt(db, "SELECT id, name, description FROM departments");
  while (stmt.executeStep()) {
    Department dept;
    dept.id = stmt.getColumn(0).getInt();
    dept.name = stmt.getColumn(1).getText();
    dept.description = stmt.getColumn(2).isNull() ? "" : stmt.getColumn(2).getText();
    departments.push_back(dept);
  }
  return departments;
}

bool DepartmentDAOSQLite::update(const Department& dept) {
  try {
    SQLite::Statement stmt(db, "UPDATE departments SET name = ?, description = ? WHERE id = ?");
    stmt.bind(1, dept.name);
    stmt.bind(2, dept.description);
    stmt.bind(3, dept.id);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error updating department: " << e.what() << std::endl;
    return false;
  }
}

bool DepartmentDAOSQLite::deleteById(int id) {
  try {
    SQLite::Statement stmt(db, "DELETE FROM departments WHERE id = ?");
    stmt.bind(1, id);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error deleting department: " << e.what() << std::endl;
    return false;
  }
}

bool DepartmentDAOSQLite::nameExists(const std::string& name) {
  SQLite::Statement stmt(db, "SELECT COUNT(*) FROM departments WHERE name = ?");
  stmt.bind(1, name);
  if (stmt.executeStep()) {
    return stmt.getColumn(0).getInt() > 0;
  }
  return false;
}