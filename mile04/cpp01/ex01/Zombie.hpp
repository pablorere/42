#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
# include <iostream>
# include <string>
# include <new>
# include <memory>
# include <vector>
class Zombie
{
    private:
        std::string name;

    public:
        Zombie();
        Zombie(std::string name);
        ~Zombie();
        void announce();
        void setName(std::string name);
        Zombie &operator=(const Zombie &other); 
};

Zombie* zombieHorde(int N, std::string name);

#endif