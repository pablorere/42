#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Deep copy ===" << std::endl;

    Dog original;
    Dog copy(original);    // copy constructor clones the Brain
    Dog assigned;
    assigned = original;   // assignment clones the Brain too

    original.makeSound();
    copy.makeSound();
    assigned.makeSound();

    std::cout << std::endl << "=== Array: half Dog, half Cat ===" << std::endl;

    const int animalCount = 4;
    Animal* animals[animalCount];

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

    std::cout << std::endl << "=== Wrong animals (non-virtual makeSound) ===" << std::endl;

    const WrongCat wrongCat;
    const WrongAnimal* wrongAnimal = &wrongCat;
    std::cout << wrongAnimal->getType() << " (via WrongAnimal*) says: ";
    wrongAnimal->makeSound();

    return 0;
}
