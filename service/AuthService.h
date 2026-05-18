#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "../dao/IUserDAO.h"
#include "../dao/IEmployeeDAO.h"
#include <memory>
#include <string>

class AuthService {
 public:
  struct LoginResult {
    bool success;
    std::string role;
    int userId;
    int employeeId;
  };

  AuthService(std::shared_ptr<IUserDAO> userDao, std::shared_ptr<IEmployeeDAO> empDao);
  LoginResult login(const std::string& username, const std::string& password);
  bool createUser(const std::string& username, const std::string& password,
                  const std::string& role);

 private:
  std::shared_ptr<IUserDAO> userDAO;
  std::shared_ptr<IEmployeeDAO> employeeDAO;
};

#endif