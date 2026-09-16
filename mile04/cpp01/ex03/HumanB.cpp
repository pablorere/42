#include "HumanB.hpp"

HumanB::HumanB(std::string Name) : Weaponb(NULL), name(Name) {}

void HumanB::attack()
{
    if (Weaponb)
        std::cout << name << ": attacks with their " << Weaponb->getType() << std::endl;
    else
        std::cout << name << ": attacks with their bare hands!" << std::endl;
}

void HumanB::setWeapon(Weapon &WeaponB)
{
    this->Weaponb = &WeaponB;
}

HumanB::~HumanB() {}