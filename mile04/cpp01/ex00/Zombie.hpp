#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
# include <iostream>
# include <string>
# include <new>
# include <memory>
class Zombie
{
    private:
        std::string name;

    public:
        Zombie();
        Zombie(std::string name);
        ~Zombie();
        void announce();
        Zombie *newZombie(std::string name);
        void randomChump(std::string name);
    
};

#endif