#include "../inc/Main.hpp"

enum intsvariables
{
	HitPoints,
	EnergyPoints,
	AttackDamage
};
// Constructor por defecto
ClapTrap::ClapTrap(void)
	: Name("default"), HitPoints(10), EnergyPoints(10), AttackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

// Parameterized constructor
ClapTrap::ClapTrap(std::string name)
	: Name(name), HitPoints(10), EnergyPoints(10), AttackDamage(0)
{
	std::cout << "ClapTrap constructor called for " << Name << std::endl;
}

// Constructor de copia
ClapTrap::ClapTrap(const ClapTrap& other)
	: Name(other.Name), HitPoints(other.HitPoints),
	  EnergyPoints(other.EnergyPoints), AttackDamage(other.AttackDamage)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
}

// Assignment operator
ClapTrap& ClapTrap::operator=(const ClapTrap& rhs)
{
	if (this != &rhs)
	{
		Name = rhs.Name;
		HitPoints = rhs.HitPoints;
		EnergyPoints = rhs.EnergyPoints;
		AttackDamage = rhs.AttackDamage;
	}
	std::cout << "ClapTrap assignment operator called" << std::endl;
	return (*this);
}

// Destructor
ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap destructor called for " << Name << std::endl;
}

// attack: ClapTrap ataca
void ClapTrap::attack(const std::string& target)
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

// takeDamage: ClapTrap takes damage
void ClapTrap::takeDamage(unsigned int amount)
{
	HitPoints -= amount;
	if (HitPoints < 0)
		HitPoints = 0;
	std::cout << Name << " takes " << amount 
		  << " points of damage! HP: " << HitPoints << std::endl;
}

// beRepaired: ClapTrap se repara
void ClapTrap::beRepaired(unsigned int amount)
{
	if (HitPoints <= 0)
	{
		std::cout << Name << " is dead and can't be repaired!" << std::endl;
		return ;
	}
	if (EnergyPoints <= 0)
	{
		std::cout  << Name << " has no energy points to repair!" << std::endl;
		return ;
	}
	EnergyPoints--;
	HitPoints += amount;
	std::cout  << Name << " is repaired by " << amount 
		  << " points! HP: " << HitPoints << std::endl;
}

// getter: retorna atributos
int ClapTrap::getter(int intsvariables) const
{
	switch (intsvariables)
	{
		case 0:
			return HitPoints;
		case 1:
			return EnergyPoints;
		case 2:
			return AttackDamage;
		default:
			return 0;
	}
}

