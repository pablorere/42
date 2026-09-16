#include "Zombie.hpp"

int main()
{
    Zombie *z1 = new Zombie("ricardo");
    z1->announce();
    Zombie *z2 = z1->newZombie("rodrigo");
    z2->announce();
    z2->randomChump("ronaldo");
    delete z1;
    delete z2;
};