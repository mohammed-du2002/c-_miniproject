#ifndef IDEPARTMENT_DAO_H
#define IDEPARTMENT_DAO_H

#include <vector>
#include "../entities/Department.h"

class IDepartmentDAO
{
public:
    virtual ~IDepartmentDAO() = default;
    virtual void createTable() = 0;
    virtual bool insert(const Department &dept) = 0;
    virtual bool update(const Department &dept) = 0;
    virtual bool deleteById(int id) = 0;
    virtual bool nameExists(const std::string &name) = 0;
    virtual std::vector<Department> getAll() = 0;
    virtual Department getById(int id) = 0;
};

#endif