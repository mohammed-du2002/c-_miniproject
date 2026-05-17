#include "ConsoleUI.h"
#include "../service/DepartmentService.h"
#include "../dao/DepartmentDAOSQLite.h"
#include <iostream>

void ConsoleUI::run()
{
    initializeDatabase();
    auto deptDAO = std::make_shared<DepartmentDAOSQLite>("hr.db");
    DepartmentService deptService(deptDAO);
    hrMenu(deptService);
}

void ConsoleUI::initializeDatabase()
{
    auto deptDAO = std::make_shared<DepartmentDAOSQLite>("hr.db");
    deptDAO->createTable();
}

void ConsoleUI::hrMenu(DepartmentService &deptSvc)
{
    int choice;
    do
    {
        std::cout << "\n--- HR Management ---\n";
        std::cout << "1. Manage Departments\n";
        std::cout << "2. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            manageDepartments(deptSvc);
            break;
        case 2:
            return;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (true);
}

void ConsoleUI::manageDepartments(DepartmentService &deptSvc)
{
    int choice;
    do
    {
        std::cout << "\n--- Manage Departments ---\n";
        std::cout << "1. List Departments\n";
        std::cout << "2. Add Department\n";
        std::cout << "3. Edit Department\n";
        std::cout << "4. Delete Department\n";
        std::cout << "5. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            listDepartments(deptSvc);
            break;
        case 2:
            addDepartment(deptSvc);
            break;
        case 3:
            editDepartment(deptSvc);
            break;
        case 4:
            deleteDepartment(deptSvc);
            break;
        case 5:
            return;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (true);
}

void ConsoleUI::listDepartments(DepartmentService &deptSvc)
{
    auto depts = deptSvc.getAllDepartments();
    if (depts.empty())
    {
        std::cout << "No departments found.\n";
        return;
    }
    std::cout << "\n=== Departments ===\n";
    std::cout << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(30) << "Description\n";
    std::cout << std::string(55, '-') << "\n";
    for (const auto &d : depts)
    {
        std::cout << std::setw(5) << d.id
                  << std::setw(20) << d.name
                  << std::setw(30) << d.description << "\n";
    }
}

void ConsoleUI::addDepartment(DepartmentService &deptSvc)
{
    std::string name, desc;
    std::cout << "Department Name: ";
    std::cin >> name;
    std::cout << "Description: ";
    std::cin >> desc;

    Department dept(name, desc);
    if (deptSvc.addDepartment(dept))
    {
        std::cout << "Department added successfully.\n";
    }
}

void ConsoleUI::editDepartment(DepartmentService &deptSvc)
{
    int id;
    std::cout << "Enter Department ID to edit: ";
    std::cin >> id;

    Department dept = deptSvc.getDepartment(id);
    if (dept.id == -1)
    {
        std::cout << "Department not found.\n";
        return;
    }

    std::string name, desc;
    std::cout << "Current: " << dept.name << " - " << dept.description << "\n";
    std::cout << "New Name (leave empty to keep): ";
    std::cin >> name;
    std::cout << "New Description (leave empty to keep): ";
    std::cin >> desc;

    if (!name.empty())
        dept.name = name;
    if (!desc.empty())
        dept.description = desc;

    if (deptSvc.updateDepartment(dept))
    {
        std::cout << "Department updated successfully.\n";
    }
}

void ConsoleUI::deleteDepartment(DepartmentService &deptSvc)
{
    int id;
    std::cout << "Enter Department ID to delete: ";
    std::cin >> id;

    if (deptSvc.removeDepartment(id))
    {
        std::cout << "Department deleted successfully.\n";
    }
    else
    {
        std::cout << "Failed to delete department.\n";
    }
}
