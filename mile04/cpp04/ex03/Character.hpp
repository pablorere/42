#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include "ICharacter.hpp"

class Character : public ICharacter {
private:
    std::string _name;
    AMateria*   _inventory[4];

public:
    Character();
    Character(std::string const & name);
    Character(const Character& other);
    Character& operator=(const Character& other);
    virtual ~Character();

    virtual std::string const & getName() const;
    virtual void equip(AMateria* materia);
    virtual void unequip(int idx);
    virtual void use(int idx, ICharacter& target);
};

#endif
