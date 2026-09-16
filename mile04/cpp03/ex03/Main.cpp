#include "./inc/Main.hpp"

int main(void) {
    std::cout << "==================================================" << std::endl;
    std::cout << "         STAGE 1: CREATION & BASIC ACTIONS        " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        ClapTrap robotA("SC-V1");
        ClapTrap robotB("CL-TP");

        std::cout << "\n--- SC-V1 begins its routine ---" << std::endl;
        robotA.attack("CL-TP");
        robotB.takeDamage(5);

        std::cout << "\n--- CL-TP tries to recover ---" << std::endl;
        robotB.beRepaired(3);
    } 

    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 2: ENERGY POINT DEPLETION          " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        ClapTrap fragile("TiredBot");

        std::cout << "\n--- TiredBot performs 10 actions to consume all energy ---" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << "[Action " << (i + 1) << "]: ";
            fragile.attack("DummyTarget");
        }

        std::cout << "\n--- TiredBot tries to perform an 11th action ---" << std::endl;
        fragile.attack("DummyTarget"); 

        std::cout << "\n--- TiredBot tries to repair itself ---" << std::endl;
        fragile.beRepaired(5); 
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 3: DEATH / DEACTIVATION            " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        ClapTrap target("DoomBot");

        std::cout << "\n--- DoomBot takes partial damage ---" << std::endl;
        target.takeDamage(4);

        std::cout << "\n--- DoomBot takes fatal damage ---" << std::endl;
        target.takeDamage(10); 

        std::cout << "\n--- DoomBot tries to act while dead ---" << std::endl;
        target.attack("SC-V1"); 

        std::cout << "\n--- DoomBot tries to repair itself while dead ---" << std::endl;
        target.beRepaired(1); 
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 4: ORTHODOX CANONICAL FORM         " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        std::cout << "--- Testing Default Constructor ---" << std::endl;
        ClapTrap defaultBot; 

        std::cout << "\n--- Testing Copy Constructor ---" << std::endl;
        ClapTrap original("Model-T");
        original.attack("air"); 

        ClapTrap cloned(original); 
        std::cout << "-> If copy constructor is correct, cloned model should also fail on 10th action." << std::endl;
        for (int i = 0; i < 9; ++i) {
            cloned.attack("shadow");
        }
        cloned.attack("shadow"); 

        std::cout << "\n--- Testing Copy Assignment Operator ---" << std::endl;
        ClapTrap copyDest("Placeholder");
        copyDest = original; 
        copyDest.attack("nothing"); 
    }
    
    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 5: SCAVTRAP INHERITANCE            " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        std::cout << "\n--- Creating ScavTrap ---" << std::endl;
        ScavTrap guardian("GateKeeper");

        std::cout << "\n--- ScavTrap Basic Actions ---" << std::endl;
        guardian.attack("Intruder");
        guardian.takeDamage(50);
        guardian.beRepaired(25);

        std::cout << "\n--- ScavTrap Special Ability ---" << std::endl;
        guardian.guardGate(); 
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 6: FRAGTRAP INHERITANCE            " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        std::cout << "\n--- Creating FragTrap ---" << std::endl;
        FragTrap fragger("HighFiver");

        std::cout << "\n--- FragTrap Basic Actions ---" << std::endl;
        fragger.attack("Bandit");
        fragger.takeDamage(80);
        fragger.beRepaired(50);

        std::cout << "\n--- FragTrap Special Ability ---" << std::endl;
        fragger.highFivesGuys(); 
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 7: DIAMONDTRAP THE MONSTER         " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        std::cout << "\n--- Creating DiamondTrap ---" << std::endl;
        // ClapTrap is constructed once, then ScavTrap and FragTrap
        DiamondTrap monster("Frankenstein");

        std::cout << "\n--- DiamondTrap Basic Actions ---" << std::endl;
        // Uses ScavTrap::attack via polymorphism / using
        monster.attack("Villager");
        
        // Damage and repair use the mixed attributes
        monster.takeDamage(50);
        monster.beRepaired(30);

        std::cout << "\n--- DiamondTrap Inherited Special Abilities ---" << std::endl;
        // Can use both parents' abilities
        monster.guardGate();
        monster.highFivesGuys();

        std::cout << "\n--- DiamondTrap Unique Special Ability ---" << std::endl;
        // Prints "Frankenstein" and the ClapTrap name "Frankenstein_clap_name"
        monster.whoAmI();
        
        std::cout << "\n--- Destruction sequence ---" << std::endl;
        // Destruction order: Diamond -> Frag -> Scav -> Clap
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "                    ALL TESTS DONE                " << std::endl;
    std::cout << "==================================================" << std::endl;

    return 0;
}