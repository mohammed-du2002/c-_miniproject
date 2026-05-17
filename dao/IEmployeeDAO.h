#ifndef IEMPLOYEE_DAO_H
#define IEMPLOYEE_DAO_H

#include <vector>
#include "../entities/Employee.h"

class IEmployeeDAO {
 public:
  virtual ~IEmployeeDAO() = default;
  virtual void createTable() = 0;
  virtual bool insert(const Employee& employee) = 0;
  virtual bool update(const Employee& employee) = 0;
  virtual bool deleteById(int id) = 0;
  virtual std::vector<Employee> getAll() = 0;
  virtual std::vector<Employee> getByDepartmentId(int departmentId) = 0;
  virtual Employee getById(int id) = 0;
  virtual Employee getByUserId(int userId) = 0;
};

#endif