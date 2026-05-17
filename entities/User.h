#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    int id;
    std::string username;
    std::string passwordHash;
    std::string role; // "HR" or "Employee"

    User() : id(-1), username(""), passwordHash(""), role("") {}
    User(const std::string &user, const std::string &pwdHash, const std::string &r)
        : id(-1), username(user), passwordHash(pwdHash), role(r) {}
};

#endif