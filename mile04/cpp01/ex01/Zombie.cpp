
#include "Zombie.hpp"


Zombie::Zombie() : name(""){};
Zombie::Zombie(std::string name) : name(name){};
Zombie::~Zombie()
{
    std::cout << name << " is destroyed." << std::endl;
};
Zombie &Zombie::operator=(const Zombie &other)
{
    if(this !=  &other)
    {
        this->name = other.name;
    }
    return (*this);
};

void Zombie::announce()
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl ;

};

void Zombie::setName(std::string name)
{
    this->name = name;
};
