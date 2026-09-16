#include "../inc/ScavTrap.hpp"

#include <iostream>


	ScavTrap::ScavTrap(void) : ClapTrap()// constructor por defect
	{
		this->Name = "defaultscav";
		this->HitPoints = 100;
		this->EnergyPoints = 50;
		this->AttackDamage = 20;
		std::cout << "ScavTrap default constructor called" << std::endl;
	} ;

	ScavTrap::ScavTrap(const ScavTrap& src) : ClapTrap(src) //constructor de copia 
	{
		std::cout << "ScavTrap " << this->Name << " copy constructor called." << std::endl;
	};
	ScavTrap& ScavTrap::operator=(const ScavTrap& rhs) // assignment operator de asignacion de copia 
	{
		std::cout << "ScavTrap copy assignment operator called." << std::endl;
		if (this != &rhs)
		{
			ClapTrap::operator=(rhs); // Copy base members safely
		}
		return *this;
	}
	ScavTrap::~ScavTrap()
	{
		std::cout << this->Name << " destructor called." << std::endl;
	};

	ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
	{
		this->HitPoints = 100;
		this->EnergyPoints = 50;
		this->AttackDamage = 20;
		std::cout << this->Name << " constructor called." << std::endl;
	};

	void ScavTrap::attack(const std::string& target)
	{
	if (HitPoints <= 0)
	{
		std::cout << Name << " is dead and can't attack!" << std::endl;
		return ;
	}
	if (EnergyPoints <= 0)
	{
		std::cout << Name << " has no energy points to attack!" << std::endl;
		return ;
	}
		EnergyPoints--;
		std::cout << Name << " attacks " << target 
			<< ", causing " << AttackDamage << " points of damage!" << std::endl;
	}

	
	void ScavTrap::guardGate()
	{
		std::cout << "I'm just a ScavTrap guarding here" << std::endl ;
	};