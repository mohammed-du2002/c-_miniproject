cmake_minimum_required(VERSION 3.16)
project(
  HRSystem
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find system libraries installed via APT
find_package(SQLite3 REQUIRED)
find_package(SQLiteCpp REQUIRED)

# Create executable
add_executable(
  hr_system
  main.cpp
  ui/ConsoleUI.cpp
  dao/DepartmentDAOSQLite.cpp
  dao/UserDAOSQLite.cpp
  dao/EmployeeDAOSQLite.cpp
  service/AuthService.cpp
  service/DepartmentService.cpp
  service/EmployeeService.cpp)

# Project include directories
target_include_directories(
  hr_system
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/entities
          ${CMAKE_CURRENT_SOURCE_DIR}/dao
          ${CMAKE_CURRENT_SOURCE_DIR}/service
          ${CMAKE_CURRENT_SOURCE_DIR}/ui
          ${SQLite3_INCLUDE_DIRS} # Ensures CMake finds SQLite3 headers
                                  # correctly
)

# Link dependencies using fallback variables
target_link_libraries(hr_system PRIVATE SQLiteCpp ${SQLite3_LIBRARIES})
