#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include <iostream>

int main()
{
    IMateriaSource* source = new MateriaSource();
    source->learnMateria(new Ice());
    source->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* ice = source->createMateria("ice");
    me->equip(ice);
    AMateria* cure = source->createMateria("cure");
    me->equip(cure);

    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);

    // Materias the character leaves on the floor are owned by main.
    AMateria* floorItems[4];
    int floorItemCount = 0;

    me->unequip(0);   // does not delete; main recovers the materia
    floorItems[floorItemCount++] = ice;

    AMateria* unknown = source->createMateria("fire");
    if (unknown)
        std::cout << "createMateria(\"fire\") -> non-null" << std::endl;
    else
        std::cout << "createMateria(\"fire\") -> NULL" << std::endl;
    delete unknown;   // deleting NULL is safe

    std::cout << std::endl << "=== Full inventory: overflow stays on the floor ===" << std::endl;
    me->equip(new Ice());   // slot 0
    me->equip(new Ice());   // slot 2
    me->equip(new Ice());   // slot 3 -> inventory now full

    AMateria* overflowIce = new Ice();
    me->equip(overflowIce);   // full -> rejected, main still owns it
    floorItems[floorItemCount++] = overflowIce;

    AMateria* overflowCure = new Cure();
    me->equip(overflowCure);   // full -> rejected
    floorItems[floorItemCount++] = overflowCure;

    me->use(3, *bob);

    std::cout << std::endl << "=== Deep copy of a Character ===" << std::endl;
    Character clone("clone");
    clone.equip(source->createMateria("cure"));
    Character other(clone);   // deep copy owns its own materias
    other.use(0, *bob);

    for (int i = 0; i < floorItemCount; i++)
        delete floorItems[i];

    delete bob;
    delete me;
    delete source;

    return 0;
}
