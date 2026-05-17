#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>

class Attendance
{
public:
    int id;
    int employeeId;
    std::string date;
    std::string clockIn;
    std::string clockOut;
    std::string status; // "Present", "Absent"

    Attendance() : id(-1), employeeId(-1), clockIn(""), clockOut(""), status("") {}
    Attendance(int empId, const std::string &d)
        : id(-1), employeeId(empId), date(d), clockIn(""), clockOut(""), status("Absent") {}
};

#endif