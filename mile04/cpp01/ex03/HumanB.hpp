#ifndef HUMANB_HPP
#define HUMANB_HPP

# include "Weapon.hpp"
# include <string>
# include <iostream>
class HumanB
{
private:
    Weapon *Weaponb;
    std::string name;
public:

    HumanB(std::string name);
    ~HumanB();
    void attack();
    void setWeapon(Weapon &WeaponB);
};


#endif