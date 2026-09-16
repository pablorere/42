#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <iostream>
#include <string>

class Weapon
{
private:
    std::string Type;
public:
    Weapon();
    Weapon(std::string Type);
    ~Weapon();
    const std::string &getType() const;
    void setType(std::string Type);
};

#endif