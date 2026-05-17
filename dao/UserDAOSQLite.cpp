#include "UserDAOSQLite.h"
#include "../entities/User.h"
#include <iostream>

UserDAOSQLite::UserDAOSQLite(const std::string& dbPath)
    : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

void UserDAOSQLite::createTable() {
  db.exec(
      "CREATE TABLE IF NOT EXISTS users ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "username TEXT UNIQUE NOT NULL, "
      "password TEXT NOT NULL, "
      "role TEXT NOT NULL)");
}

bool UserDAOSQLite::insert(const User& user) {
  try {
    SQLite::Statement stmt(db, "INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
    stmt.bind(1, user.username);
    stmt.bind(2, user.passwordHash);
    stmt.bind(3, user.role);
    stmt.exec();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Insert error: " << e.what() << std::endl;
    return false;
  }
}

User UserDAOSQLite::getById(int id) {
  try {
    SQLite::Statement stmt(db, "SELECT id, username, password, role FROM users WHERE id = ?");
    stmt.bind(1, id);
    if (stmt.executeStep()) {
      User user;
      user.id = stmt.getColumn(0).getInt();
      user.username = stmt.getColumn(1).getString();
      user.passwordHash = stmt.getColumn(2).getString();
      user.role = stmt.getColumn(3).getString();
      return user;
    }
  } catch (const std::exception& e) {
    std::cerr << "Get by ID error: " << e.what() << std::endl;
  }
  return User();  // Return empty user if not found or on error
}

User UserDAOSQLite::getByUsername(const std::string& username) {
  try {
    SQLite::Statement stmt(db, "SELECT id, username, password, role FROM users WHERE username = ?");
    stmt.bind(1, username);
    if (stmt.executeStep()) {
      User user;
      user.id = stmt.getColumn(0).getInt();
      user.username = stmt.getColumn(1).getString();
      user.passwordHash = stmt.getColumn(2).getString();
      user.role = stmt.getColumn(3).getString();
      return user;
    }
  } catch (const std::exception& e) {
    std::cerr << "Get by username error: " << e.what() << std::endl;
  }
  return User();  // Return empty user if not found or on error
}

std::vector<User> UserDAOSQLite::getAll() {
  std::vector<User> users;
  try {
    SQLite::Statement stmt(db, "SELECT id, username, password, role FROM users");
    while (stmt.executeStep()) {
      User user;
      user.id = stmt.getColumn(0).getInt();
      user.username = stmt.getColumn(1).getString();
      user.passwordHash = stmt.getColumn(2).getString();
      user.role = stmt.getColumn(3).getString();
      users.push_back(user);
    }
  } catch (const std::exception& e) {
    std::cerr << "Get all error: " << e.what() << std::endl;
  }
  return users;
}

bool UserDAOSQLite::update(const User& user) {
  try {
    SQLite::Statement stmt(db,
                           "UPDATE users SET username = ?, password = ?, role = ? WHERE id = ?");
    stmt.bind(1, user.username);
    stmt.bind(2, user.passwordHash);
    stmt.bind(3, user.role);
    stmt.bind(4, user.id);
    return stmt.exec() > 0;
  } catch (const std::exception& e) {
    std::cerr << "Update error: " << e.what() << std::endl;
    return false;
  }
}

bool UserDAOSQLite::deleteById(int id) {
  try {
    SQLite::Statement stmt(db, "DELETE FROM users WHERE id = ?");
    stmt.bind(1, id);
    return stmt.exec() > 0;
  } catch (const std::exception& e) {
    std::cerr << "Delete error: " << e.what() << std::endl;
    return false;
  }
}

bool UserDAOSQLite::usernameExists(const std::string& username) {
  try {
    SQLite::Statement stmt(db, "SELECT COUNT(*) FROM users WHERE username = ?");
    stmt.bind(1, username);
    if (stmt.executeStep()) {
      return stmt.getColumn(0).getInt() > 0;
    }
  } catch (const std::exception& e) {
    std::cerr << "Username exists check error: " << e.what() << std::endl;
  }
  return false;
}