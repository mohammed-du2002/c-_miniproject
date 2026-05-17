#ifndef IUSER_DAO_H
#define IUSER_DAO_H

#include <vector>
#include "../entities/User.h"

class IUserDAO {
 public:
  virtual ~IUserDAO() = default;
  virtual void createTable() = 0;
  virtual bool insert(const User& user) = 0;
  virtual bool update(const User& user) = 0;
  virtual bool deleteById(int id) = 0;
  virtual bool usernameExists(const std::string& username) = 0;
  virtual std::vector<User> getAll() = 0;
  virtual User getById(int id) = 0;
  virtual User getByUsername(const std::string& username) = 0;
};

#endif