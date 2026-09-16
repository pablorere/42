#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

Cat::Cat() : AAnimal() {
    this->type = "Cat";
    this->_brain = new Brain();
    std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : AAnimal(other) {
    this->type = other.type;
    this->_brain = new Brain(*other._brain);
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat copy assignment operator called" << std::endl;
    if (this != &other) {
        AAnimal::operator=(other);
        Brain* newBrain = new Brain(*other._brain);
        delete this->_brain;
        this->_brain = newBrain;
    }
    return *this;
}

Cat::~Cat() {
    delete this->_brain;
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meow! Meow!" << std::endl;
}
