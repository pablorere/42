#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Brain;

class Cat : public Animal {
private:
    Brain* _brain;

public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    virtual ~Cat();

    virtual void makeSound() const;
};

#endif
