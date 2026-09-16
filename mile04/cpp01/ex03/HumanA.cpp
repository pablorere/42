#include "HumanA.hpp"

HumanA::HumanA(std::string Name, Weapon &WeaponA) : Weapona(WeaponA), name(Name) {};
void HumanA::attack()
{
    std::cout << name << ": Attacks with their " << Weapona.getType() << std::endl;
};

void HumanA::setWeapon(Weapon &WeaponA)
{
    Weapona.setType(WeaponA.getType());
};

HumanA::~HumanA()
{
}
