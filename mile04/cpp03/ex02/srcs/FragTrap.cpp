#include "../inc/FragTrap.hpp"

#include <iostream>


	FragTrap::FragTrap(void) : ClapTrap("defaultFrag")// constructor por defect
	{
		this->HitPoints = 100;
		this->EnergyPoints = 100;
		this->AttackDamage = 30;
		std::cout << "FragTrap default constructor called" << std::endl;
	} ;

	FragTrap::FragTrap(const FragTrap& src) : ClapTrap(src) //constructor de copia 
	{
		std::cout << "FragTrap " << this->Name << " copy constructor called." << std::endl;
	};
	FragTrap& FragTrap::operator=(const FragTrap& rhs) // assignment operator de asignacion de copia 
	{
		std::cout << "FragTrap copy assignment operator called." << std::endl;
		if (this != &rhs)
			ClapTrap::operator=(rhs); // Copy base members safely
		return *this;
	}
	FragTrap::~FragTrap()
	{
		std::cout << this->Name << " destructor called." << std::endl;
	};

	FragTrap::FragTrap(std::string name) : ClapTrap(name)
	{
		this->HitPoints = 100;
		this->EnergyPoints = 100;
		this->AttackDamage = 30;
		std::cout << this->Name << " constructor called." << std::endl;
	};
	
	void	FragTrap::highFivesGuys( void )
	{
		std::string	five;

		std::cout << "FragTrap " << Name << " requests a high five! (press enter to high five)";
		std::getline(std::cin, five);
	}