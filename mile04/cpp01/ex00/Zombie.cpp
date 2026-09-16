
#include "Zombie.hpp"


Zombie::Zombie() : name(NULL){};
Zombie::Zombie(std::string name) : name(name){};
Zombie::~Zombie()
{
    std::cout << name << std::endl;
};

void Zombie::announce()
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl ;

};
