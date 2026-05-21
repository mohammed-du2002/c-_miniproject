#ifndef ATTENDANCE_DAO_SQLITE_H
#define ATTENDANCE_DAO_SQLITE_H

#include "IAttendanceDAO.h"
#include <SQLiteCpp/Database.h>
#include <string>

class AttendanceDAOSQLite : public IAttendanceDAO {
 public:
  explicit AttendanceDAOSQLite(const std::string& dbPath);
  void createTable() override;
  bool insert(const Attendance& att) override;
  bool update(const Attendance& att) override;
  bool deleteById(int id) override;
  Attendance getById(int id) override;
  Attendance getByEmployeeAndDate(int employeeId, const std::string& date) override;
  std::vector<Attendance> getAll() override;
  std::vector<Attendance> getByEmployee(int employeeId) override;
  std::vector<Attendance> getByEmployeeAndMonth(int employeeId, const std::string& month) override;
  std::vector<Attendance> getByEmployeeAndDateRange(int employeeId, const std::string& startDate,
                                                    const std::string& endDate) override;
  std::vector<Attendance> getByDateRange(const std::string& startDate,
                                         const std::string& endDate) override;
  int countPresentDays(int employeeId, const std::string& month);

 private:
  SQLite::Database db;
};

#endif