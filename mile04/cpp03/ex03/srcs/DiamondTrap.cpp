#include "../inc/DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap(void) : ClapTrap("default_clap_name")
{
	this->Name = "default";
	ClapTrap::Name = "default_clap_name";
	this->HitPoints = 100;
	this->EnergyPoints = 50;
	this->AttackDamage = 30;
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& src)
	: ClapTrap(src), ScavTrap(src), FragTrap(src)
{
	this->Name = src.Name;
	std::cout << "DiamondTrap " << this->Name << " copy constructor called." << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& rhs)
{
	std::cout << "DiamondTrap copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
		ClapTrap::operator=(rhs);
		this->Name = rhs.Name;
	}
	return *this;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << this->Name << " destructor called." << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name")
{
	this->Name = name;
	ClapTrap::Name = name + "_clap_name";
	this->HitPoints = 100;
	this->EnergyPoints = 50;
	this->AttackDamage = 30;
	std::cout << this->Name << " constructor called." << std::endl;
}

void DiamondTrap::attack(const std::string& target)
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

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap name: " << this->Name
		<< " | ClapTrap name: " << ClapTrap::Name << std::endl;
}
