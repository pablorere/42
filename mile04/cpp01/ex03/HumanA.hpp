#ifndef HUMANA_HPP
#define HUMANA_HPP

# include "Weapon.hpp"
# include <string>
# include <iostream>
class HumanA
{
private:
    Weapon  &Weapona;
    std::string name;
public:
    HumanA();
    HumanA(std::string Name, Weapon &WeaponA);
    ~HumanA();
    void attack();
    void setWeapon(Weapon &WeaponA);
};


#endif