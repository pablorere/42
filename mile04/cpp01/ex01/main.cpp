
#include "Zombie.hpp"

int main()
{
    int N = 9;
    Zombie *horde = zombieHorde(N, "Claudio");
    
    if (horde)
    {
        for (int i = 0; i < N; i++)
        {
            horde[i].announce();
        }
        delete[] horde;
    }
    return 0;
}