#include "megaphone.hpp"

int main(int ac, char **av)
{
    int i = 1;
    std::string texts;
    while (av[i]){
        ToUpper arg(av[i]);
        texts += arg.scream();
        i++;
    }
    if(ac == 1){
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    }
    else
        std::cout << texts << std::endl;
   
    return (0);
}