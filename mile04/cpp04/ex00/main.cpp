#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Correct animals (virtual) ===" << std::endl;

    const Animal* animal = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << dog->getType() << " says: ";
    dog->makeSound();
    std::cout << cat->getType() << " says: ";
    cat->makeSound();
    std::cout << animal->getType() << " says: ";
    animal->makeSound();

    delete animal;   // virtual destructor -> correct chain
    delete dog;
    delete cat;

    std::cout << std::endl << "=== Wrong animals (non-virtual makeSound) ===" << std::endl;

    const WrongCat wrongCat;
    const WrongAnimal* wrongAnimal = &wrongCat;

    // getType() is inherited, but makeSound() is NOT virtual:
    // the base version runs even though the object is a WrongCat.
    std::cout << wrongAnimal->getType() << " (via WrongAnimal*) says: ";
    wrongAnimal->makeSound();

    return 0;
}
