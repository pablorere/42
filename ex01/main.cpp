#include "main.hpp"

int main()
{
    std::string flag;
    phonebook ph1;

    while (1)
    {
        std::cout << "Comando (ADD, SEARCH, EXIT): " << std::flush;
        flag = getInput(6, ALPHA);

        if (flag == "ADD")
            ph1.ADD();
        else if (flag == "SEARCH")
            ph1.SEARCH();
        else if (flag == "EXIT")
            break;
        else
            std::cout << "Comando invalido" << std::endl;
    }

    return (0);
}


// LO QUE CREO QUE ME FAALTA : terminar el search , que el add pueda agregar espacios y que se pueda recibir el nombre correcto pero con max de 32 char 