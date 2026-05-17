#ifndef PAYROLL_H
#define PAYROLL_H

#include <string>

class Payroll
{
public:
    int id;
    int employeeId;
    std::string month;
    double basicSalary;
    double deductions;
    double bonus;
    double netSalary;
    std::string generatedDate;

    Payroll() : id(-1), employeeId(-1), basicSalary(0.0), deductions(0.0), bonus(0.0), netSalary(0.0) {}
    Payroll(int empId, const std::string &m, double basic, double ded, double bon)
        : id(-1), employeeId(empId), month(m), basicSalary(basic), deductions(ded), bonus(bon), netSalary(0.0) {}
};

#endif