#include "AttendanceService.h"
#include "../entities/Employee.h"
#include <iostream>

AttendanceService::AttendanceService(std::shared_ptr<IAttendanceDAO> attDAO,
                                     std::shared_ptr<IEmployeeDAO> empDAO)
    : attendanceDAO(attDAO), employeeDAO(empDAO) {}

bool AttendanceService::clockIn(int employeeId, const std::string& date, const std::string& time) {
  Employee emp = employeeDAO->getById(employeeId);
  if (emp.id == -1) {
    std::cerr << "Error: Employee not Found.\n";
    return false;
  }
  Attendance existing = attendanceDAO->getByEmployeeAndDate(employeeId, date);
  if (existing.id != -1) {
    if (!existing.clockIn.empty()) {
      std::cerr << "Error: Already Clocked In Today.\n";
      return false;
    }
    existing.clockIn = time;
    existing.status = "Present";
    return attendanceDAO->update(existing);
  }

  Attendance att;
  att.employeeId = employeeId;
  att.date = date;
  att.clockIn = time;
  att.status = "Present";

  return attendanceDAO->insert(att);
}

bool AttendanceService::clockOut(int employeeId, const std::string& date, const std::string& time) {
  Attendance existing = attendanceDAO->getByEmployeeAndDate(employeeId, date);
  if (existing.id == -1) {
    std::cerr << "Error: No attendance record found for today.\n";
    return false;
  }

  if (existing.clockIn.empty()) {
    std::cerr << "Error: Must clock in before clocking out.\n";
    return false;
  }

  if (!existing.clockOut.empty()) {
    std::cerr << "Error: Already clocked out today.\n";
    return false;
  }

  existing.clockOut = time;
  return attendanceDAO->update(existing);
}

bool AttendanceService::markAbsent(int employeeId, const std::string& date) {
  Attendance existing = attendanceDAO->getByEmployeeAndDate(employeeId, date);
  if (existing.id != -1) {
    existing.clockIn = "";
    existing.clockOut = "";
    existing.status = "Absent";
    return attendanceDAO->update(existing);
  }

  Attendance att;
  att.employeeId = employeeId;
  att.date = date;
  att.status = "Absent";
  return attendanceDAO->insert(att);
}

std::vector<Attendance> AttendanceService::getAttendanceByRange(const std::string& startDate,
                                                                const std::string& endDate) {
  return attendanceDAO->getByDateRange(startDate, endDate);
}

std::vector<Attendance> AttendanceService::getAttendanceByEmployeeAndRange(
    int employeeId, const std::string& startDate, const std::string& endDate) {
  return attendanceDAO->getByEmployeeAndDateRange(employeeId, startDate, endDate);
}

std::vector<Attendance> AttendanceService::getEmployeeAttendance(int employeeId) {
  return attendanceDAO->getByEmployee(employeeId);
}

std::vector<Attendance> AttendanceService::getAllAttendance() {
  return attendanceDAO->getAll();
}

Attendance AttendanceService::getAttendanceByDate(int employeeId, const std::string& date) {
  return attendanceDAO->getByEmployeeAndDate(employeeId, date);
}