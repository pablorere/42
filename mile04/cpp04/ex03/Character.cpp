#include "Character.hpp"
#include "AMateria.hpp"

Character::Character() : _name("") {
    for (int i = 0; i < 4; i++)
        _inventory[i] = 0;
}

Character::Character(std::string const & name) : _name(name) {
    for (int i = 0; i < 4; i++)
        _inventory[i] = 0;
}

Character::Character(const Character& other) : _name(other._name) {
    for (int i = 0; i < 4; i++)
    {
        if (other._inventory[i] != 0)
            _inventory[i] = other._inventory[i]->clone();
        else
            _inventory[i] = 0;
    }
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        _name = other._name;
        for (int i = 0; i < 4; i++)
        {
            delete _inventory[i];
            if (other._inventory[i] != 0)
                _inventory[i] = other._inventory[i]->clone();
            else
                _inventory[i] = 0;
        }
    }
    return *this;
}

Character::~Character() {
    for (int i = 0; i < 4; i++)
        delete _inventory[i];
}

std::string const & Character::getName() const {
    return _name;
}

void Character::equip(AMateria* materia) {
    for (int i = 0; i < 4; i++) {
        if (_inventory[i] == 0) {
            _inventory[i] = materia;
            return;
        }
    }
    // Inventory full: nothing happens, ownership remains with the caller.
}

void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4)
        _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < 4 && _inventory[idx])
        _inventory[idx]->use(target);
}
