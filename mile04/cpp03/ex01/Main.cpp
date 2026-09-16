#include "./inc/Main.hpp"

int main(void) {
    std::cout << "==================================================" << std::endl;
    std::cout << "          STAGE 1: CREATION & BASIC ACTIONS       " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // Testing normal initialization and actions
        ClapTrap robotA("SC-V1");
        ClapTrap robotB("CL-TP");

        std::cout << "\n--- SC-V1 begins its routine ---" << std::endl;
        robotA.attack("CL-TP");
        robotB.takeDamage(5); // Manual simulation of damage application

        std::cout << "\n--- CL-TP tries to recover ---" << std::endl;
        robotB.beRepaired(3);

        std::cout << "\n--- Action sequence completed ---" << std::endl;
    } // Here destructors will be called automatically, testing proper destruction order

    std::cout << "\n==================================================" << std::endl;
    std::cout << "          STAGE 2: ENERGY POINT DEPLETION         " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // ClapTrap starts with 10 Energy Points. We will exhaust them.
        ClapTrap fragile("TiredBot");

        std::cout << "\n--- TiredBot performs 10 actions to consume all energy ---" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << "[Action " << (i + 1) << "]: ";
            fragile.attack("DummyTarget");
        }

        std::cout << "\n--- TiredBot tries to perform an 11th action ---" << std::endl;
        fragile.attack("DummyTarget"); // Should fail due to 0 Energy Points

        std::cout << "\n--- TiredBot tries to repair itself ---" << std::endl;
        fragile.beRepaired(5); // Should also fail due to 0 Energy Points
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "          STAGE 3: DEATH / DEACTIVATION           " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // ClapTrap starts with 10 Hit Points. We will deal fatal damage.
        ClapTrap target("DoomBot");

        std::cout << "\n--- DoomBot takes partial damage ---" << std::endl;
        target.takeDamage(4);

        std::cout << "\n--- DoomBot takes fatal damage ---" << std::endl;
        target.takeDamage(10); // Extinguishes HP to 0 (HP is now technically -4, capped to 0)

        std::cout << "\n--- DoomBot tries to act while dead ---" << std::endl;
        target.attack("SC-V1"); // Should fail

        std::cout << "\n--- DoomBot tries to repair itself while dead ---" << std::endl;
        target.beRepaired(1); // Should fail

        std::cout << "\n--- DoomBot takes damage while already dead ---" << std::endl;
        target.takeDamage(5); // Should still execute (just prints a status or handles dead state gracefully)
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "          STAGE 4: ORTHODOX CANONICAL FORM        " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        std::cout << "--- Testing Default Constructor ---" << std::endl;
        ClapTrap defaultBot; // Tests ClapTrap(void)

        std::cout << "\n--- Testing Copy Constructor ---" << std::endl;
        ClapTrap original("Model-T");
        original.attack("air"); // Consumes 1 Energy (Model-T has 9 Energy left)

        ClapTrap cloned(original); // Tests ClapTrap(const ClapTrap& src)
        std::cout << "-> If copy constructor is correct, cloned model should also fail on 10th action." << std::endl;
        for (int i = 0; i < 9; ++i) {
            cloned.attack("shadow");
        }
        cloned.attack("shadow"); // 10th action on cloned (should fail because it started with 9 Energy)

        std::cout << "\n--- Testing Copy Assignment Operator ---" << std::endl;
        ClapTrap copyDest("Placeholder");
        copyDest = original; // Tests operator=(const ClapTrap& rhs)
        copyDest.attack("nothing"); // Should work because original still had energy
    }
    std::cout << "\n==================================================" << std::endl;
    std::cout << "         STAGE 5: SCAVTRAP INHERITANCE            " << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        std::cout << "\n--- Creating ScavTrap ---" << std::endl;
        // ClapTrap is constructed first, then ScavTrap
        ScavTrap guardian("GateKeeper");

        std::cout << "\n--- ScavTrap Basic Actions ---" << std::endl;
        // Calls the overridden ScavTrap::attack, not ClapTrap::attack
        guardian.attack("Intruder");
        
        // takeDamage y beRepaired se heredan de ClapTrap directamente
        guardian.takeDamage(50);
        guardian.beRepaired(25);

        std::cout << "\n--- ScavTrap Special Ability ---" << std::endl;
        // Invoke the new "gate keeper mode" ability
        guardian.guardGate(); 
        
        std::cout << "\n--- Destruction sequence ---" << std::endl;
        // Leaving the scope destroys objects in reverse order
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "                    ALL TESTS DONE                " << std::endl;
    std::cout << "==================================================" << std::endl;

    return 0;
}