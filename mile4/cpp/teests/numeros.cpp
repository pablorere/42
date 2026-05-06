#include <iostream>
#include "InputHandler.hpp"

int main()
{
    std::cout << "Introduce 5 numeros: " << std::endl;
    std::string n = getInput(5, NUMERIC);
    std::cout << "\nResultado: " << n << std::endl;

    std::cout << "Introduce 5 letras: " << std::endl;
    std::string l = getInput(5, ALPHA);
    std::cout << "\nResultado: " << l << std::endl;

    std::cout << "Introduce 8 caracteres alfanumericos: " << std::endl;
    std::string an = getInput(8, ALPHANUM);
    std::cout << "\nResultado: " << an << std::endl;

    return (0);
}