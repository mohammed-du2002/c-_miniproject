#ifndef EMPLOYEE_DAO_SQLITE_H
#define EMPLOYEE_DAO_SQLITE_H

#include "IEmployeeDAO.h"
#include <SQLiteCpp/Database.h>
#include <string>

class EmployeeDAOSQLite : public IEmployeeDAO {
 public:
  explicit EmployeeDAOSQLite(const std::string& dbPath);
  void createTable() override;
  bool insert(const Employee& employee) override;
  bool update(const Employee& employee) override;
  bool deleteById(int id) override;
  std::vector<Employee> getAll() override;
  std::vector<Employee> getByDepartmentId(int departmentId) override;
  Employee getById(int id) override;
  Employee getByUserId(int userId) override;

 private:
  SQLite::Database db;
};

#endif