#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Array: half Dog, half Cat ===" << std::endl;

    const int animalCount = 4;
    AAnimal* animals[animalCount];

    for (int i = 0; i < animalCount; i++)
    {
        if (i < animalCount / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < animalCount; i++)
    {
        std::cout << animals[i]->getType() << ": ";
        animals[i]->makeSound();
    }

    for (int i = 0; i < animalCount; i++)
        delete animals[i];   // virtual destructor frees each Brain

    // AAnimal is abstract: the line below must NOT compile.
    // AAnimal animal;

    std::cout << std::endl << "=== Wrong animals (non-virtual makeSound) ===" << std::endl;

    const WrongCat wrongCat;
    const WrongAnimal* wrongAnimal = &wrongCat;
    std::cout << wrongAnimal->getType() << " (via WrongAnimal*) says: ";
    wrongAnimal->makeSound();

    return 0;
}
