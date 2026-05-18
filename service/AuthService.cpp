#include "AuthService.h"
#include <iostream>

AuthService::AuthService(std::shared_ptr<IUserDAO> userDao, std::shared_ptr<IEmployeeDAO> empDao)
    : userDAO(userDao), employeeDAO(empDao) {}

AuthService::LoginResult AuthService::login(const std::string& username,
                                            const std::string& password) {
  LoginResult result;
  result.success = false;
  result.userId = -1;
  result.employeeId = -1;

  User user = userDAO->getByUsername(username);
  if (user.id == -1) {
    std::cout << "User not found.\n";
    return result;
  }

  if (user.passwordHash != password) {
    std::cout << "Incorrect password.\n";
    return result;
  }

  result.success = true;
  result.role = user.role;
  result.userId = user.id;

  if (user.role == "Employee") {
    Employee emp = employeeDAO->getByUserId(user.id);
    result.employeeId = emp.id;
  }

  return result;
}

bool AuthService::createUser(const std::string& username, const std::string& password,
                             const std::string& role) {
  if (userDAO->usernameExists(username)) {
    std::cerr << "Username already exists.\n";
    return false;
  }

  User newUser;
  newUser.username = username;
  newUser.passwordHash = password;
  newUser.role = role;

  return userDAO->insert(newUser);
}