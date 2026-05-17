#ifndef DEPARTMENT_DAO_SQLITE_H
#define DEPARTMENT_DAO_SQLITE_H

#include "IDepartmentDAO.h"
#include <SQLiteCpp/Database.h>
#include <vector>
#include <string>

class DepartmentDAOSQLite : public IDepartmentDAO
{
public:
    explicit DepartmentDAOSQLite(const std::string &dbPath);
    ~DepartmentDAOSQLite() override;

    void createTable() override;
    bool insert(const Department &dept) override;
    bool update(const Department &dept) override;
    bool deleteById(int id) override;
    bool nameExists(const std::string &name) override;
    std::vector<Department> getAll() override;
    Department getById(int id) override;

private:
    SQLite::Database db;
};

#endif