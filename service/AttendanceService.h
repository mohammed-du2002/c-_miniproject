#ifndef ATTENDANCE_SERVICE_H
#define ATTENDANCE_SERVICE_H

#include "../dao/IAttendanceDAO.h"
#include "../dao/IEmployeeDAO.h"
#include "../entities/Attendance.h"
#include <vector>
#include <memory>
#include <string>

class AttendanceService {
 public:
  AttendanceService(std::shared_ptr<IAttendanceDAO> attDAO, std::shared_ptr<IEmployeeDAO> empDAO);
  bool clockIn(int employeeId, const std::string& date, const std::string& time);
  bool clockOut(int employeeId, const std::string& date, const std::string& time);
  bool markAbsent(int employeeId, const std::string& date);
  std::vector<Attendance> getEmployeeAttendance(int employeeId);
  std::vector<Attendance> getAttendanceByRange(const std::string& startDate,
                                               const std::string& endDate);
  std::vector<Attendance> getAttendanceByEmployeeAndRange(int employeeId,
                                                          const std::string& startDate,
                                                          const std::string& endDate);
  std::vector<Attendance> getAllAttendance();
  Attendance getAttendanceByDate(int employeeId, const std::string& date);

 private:
  std::shared_ptr<IAttendanceDAO> attendanceDAO;
  std::shared_ptr<IEmployeeDAO> employeeDAO;
};

#endif