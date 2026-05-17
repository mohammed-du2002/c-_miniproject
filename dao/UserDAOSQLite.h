#ifndef USER_DAO_SQLITE_H
#define USER_DAO_SQLITE_H

#include "IUserDAO.h"
#include <SQLiteCpp/Database.h>
#include <string>

class UserDAOSQLite : public IUserDAO {
 public:
  explicit UserDAOSQLite(const std::string& dbPath);
  void createTable() override;
  bool insert(const User& user) override;
  bool update(const User& user) override;
  bool deleteById(int id) override;
  bool usernameExists(const std::string& username) override;
  std::vector<User> getAll() override;
  User getById(int id) override;
  User getByUsername(const std::string& username) override;

 private:
  SQLite::Database db;
};

#endif