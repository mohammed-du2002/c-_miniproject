#ifndef IATTENDANCE_DAO_H
#define IATTENDANCE_DAO_H

#include <vector>
#include "../entities/Attendance.h"

class IAttendanceDAO {
 public:
  virtual ~IAttendanceDAO() = default;
  virtual void createTable() = 0;
  virtual bool insert(const Attendance& att) = 0;
  virtual bool update(const Attendance& att) = 0;
  virtual bool deleteById(int id) = 0;
  virtual Attendance getById(int id) = 0;
  virtual Attendance getByEmployeeAndDate(int employeeId, const std::string& date) = 0;
  virtual std::vector<Attendance> getAll() = 0;
  virtual std::vector<Attendance> getByEmployee(int employeeId) = 0;
  virtual std::vector<Attendance> getByEmployeeAndMonth(int employeeId,
                                                        const std::string& month) = 0;
  virtual std::vector<Attendance> getByEmployeeAndDateRange(int employeeId,
                                                            const std::string& startDate,
                                                            const std::string& endDate) = 0;
  virtual std::vector<Attendance> getByDateRange(const std::string& startDate,
                                                 const std::string& endDate) = 0;
};

#endif