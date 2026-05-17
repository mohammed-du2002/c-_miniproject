#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <memory>
#include <string>

class DepartmentService;

class ConsoleUI
{
public:
    void run();

private:
    void hrMenu(DepartmentService &deptSvc);
    void initializeDatabase();

    /* Department Management */
    void manageDepartments(DepartmentService &deptSvc);
    void listDepartments(DepartmentService &deptSvc);
    void addDepartment(DepartmentService &deptSvc);
    void editDepartment(DepartmentService &deptSvc);
    void deleteDepartment(DepartmentService &deptSvc);
};

#endif