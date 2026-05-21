#include "AttendanceDAOSQLite.h"
#include "../entities/Attendance.h"
#include <iostream>

AttendanceDAOSQLite::AttendanceDAOSQLite(const std::string& dbPath)
    : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

void AttendanceDAOSQLite::createTable() {
  db.exec(
      "CREATE TABLE IF NOT EXISTS attendance ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "employee_id INTEGER NOT NULL,"
      "date TEXT NOT NULL,"
      "clock_in TEXT,"
      "clock_out TEXT,"
      "status TEXT NOT NULL,"
      "FOREIGN KEY(employee_id) REFERENCES employees(id))");
}

bool AttendanceDAOSQLite::insert(const Attendance& att) {
  try {
    SQLite::Statement stmt(db,
                           "INSERT INTO attendance (employee_id, date, clock_in, clock_out, "
                           "status) VALUES (?, ?, ?, ?, ?)");
    stmt.bind(1, att.employeeId);
    stmt.bind(2, att.date);
    stmt.bind(3, att.clockIn);
    stmt.bind(4, att.clockOut);
    stmt.bind(5, att.status);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error inserting attendance: " << e.what() << std::endl;
    return false;
  }
}

Attendance AttendanceDAOSQLite::getById(int id) {
  try {
    SQLite::Statement stmt(
        db,
        "SELECT id, employee_id, date, clock_in, clock_out, status FROM attendance WHERE id = ?");
    stmt.bind(1, id);
    if (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      return att;
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching attendance by ID: " << e.what() << std::endl;
  }
  return Attendance();
}

std::vector<Attendance> AttendanceDAOSQLite::getAll() {
  std::vector<Attendance> attendances;
  try {
    SQLite::Statement stmt(
        db, "SELECT id, employee_id, date, clock_in, clock_out, status FROM attendance");
    while (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      attendances.push_back(att);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching all attendances: " << e.what() << std::endl;
  }
  return attendances;
}

std::vector<Attendance> AttendanceDAOSQLite::getByEmployee(int employeeId) {
  std::vector<Attendance> attendances;
  try {
    SQLite::Statement stmt(db,
                           "SELECT id, employee_id, date, clock_in, clock_out, status FROM "
                           "attendance WHERE employee_id = ? ORDER BY date DESC");
    stmt.bind(1, employeeId);
    while (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      attendances.push_back(att);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching attendances by employee: " << e.what() << std::endl;
  }
  return attendances;
}

std::vector<Attendance> AttendanceDAOSQLite::getByEmployeeAndMonth(int employeeId,
                                                                   const std::string& month) {
  std::vector<Attendance> attendances;
  try {
    SQLite::Statement stmt(db,
                           "SELECT id, employee_id, date, clock_in, clock_out, status FROM "
                           "attendance WHERE employee_id = ? AND strftime('%Y-%m', date) = ? "
                           "ORDER BY date DESC");
    stmt.bind(1, employeeId);
    stmt.bind(2, month);
    while (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      attendances.push_back(att);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching attendances by employee and month: " << e.what() << std::endl;
  }
  return attendances;
}

std::vector<Attendance> AttendanceDAOSQLite::getByEmployeeAndDateRange(int employeeId,
                                                                       const std::string& startDate,
                                                                       const std::string& endDate) {
  std::vector<Attendance> attendances;
  try {
    SQLite::Statement stmt(db,
                           "SELECT id, employee_id, date, clock_in, clock_out, status FROM "
                           "attendance WHERE employee_id = ? AND date BETWEEN ? AND ? "
                           "ORDER BY date DESC");
    stmt.bind(1, employeeId);
    stmt.bind(2, startDate);
    stmt.bind(3, endDate);
    while (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      attendances.push_back(att);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching attendances by employee and date range: " << e.what() << std::endl;
  }
  return attendances;
}

std::vector<Attendance> AttendanceDAOSQLite::getByDateRange(const std::string& startDate,
                                                            const std::string& endDate) {
  std::vector<Attendance> attendances;
  try {
    SQLite::Statement stmt(db,
                           "SELECT id, employee_id, date, clock_in, clock_out, status FROM "
                           "attendance WHERE date BETWEEN ? AND ? ORDER BY date DESC");
    stmt.bind(1, startDate);
    stmt.bind(2, endDate);
    while (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      attendances.push_back(att);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching attendances by date range: " << e.what() << std::endl;
  }
  return attendances;
}

Attendance AttendanceDAOSQLite::getByEmployeeAndDate(int employeeId, const std::string& date) {
  try {
    SQLite::Statement stmt(db,
                           "SELECT id, employee_id, date, clock_in, clock_out, status FROM "
                           "attendance WHERE employee_id = ? AND date = ?");
    stmt.bind(1, employeeId);
    stmt.bind(2, date);
    if (stmt.executeStep()) {
      Attendance att;
      att.id = stmt.getColumn(0).getInt();
      att.employeeId = stmt.getColumn(1).getInt();
      att.date = stmt.getColumn(2).getString();
      att.clockIn = stmt.getColumn(3).getString();
      att.clockOut = stmt.getColumn(4).getString();
      att.status = stmt.getColumn(5).getString();
      return att;
    }
  } catch (const std::exception& e) {
    std::cerr << "Error fetching attendance by employee and date: " << e.what() << std::endl;
  }
  return Attendance();
}

bool AttendanceDAOSQLite::update(const Attendance& att) {
  try {
    SQLite::Statement stmt(db,
                           "UPDATE attendance SET employee_id = ?, date = ?, clock_in = ?, "
                           "clock_out = ?, status = ? WHERE id = ?");
    stmt.bind(1, att.employeeId);
    stmt.bind(2, att.date);
    stmt.bind(3, att.clockIn);
    stmt.bind(4, att.clockOut);
    stmt.bind(5, att.status);
    stmt.bind(6, att.id);
    return stmt.exec() > 0;
  } catch (const std::exception& e) {
    std::cerr << "Error updating attendance: " << e.what() << std::endl;
    return false;
  }
}

bool AttendanceDAOSQLite::deleteById(int id) {
  try {
    SQLite::Statement stmt(db, "DELETE FROM attendance WHERE id = ?");
    stmt.bind(1, id);
    return stmt.exec() > 0;
  } catch (const std::exception& e) {
    std::cerr << "Error deleting attendance: " << e.what() << std::endl;
    return false;
  }
}

int AttendanceDAOSQLite::countPresentDays(int employeeId, const std::string& month) {
  try {
    SQLite::Statement stmt(db,
                           "SELECT COUNT(*) FROM attendance WHERE employee_id = ? AND "
                           "strftime('%Y-%m', date) = ? AND status = 'Present'");
    stmt.bind(1, employeeId);
    stmt.bind(2, month + "%");
    if (stmt.executeStep()) {
      return stmt.getColumn(0).getInt();
    }
  } catch (const std::exception& e) {
    std::cerr << "Error counting present days: " << e.what() << std::endl;
  }
  return 0;
}
