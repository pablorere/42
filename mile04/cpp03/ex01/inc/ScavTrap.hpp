#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap 
{
	public:
		ScavTrap(void);
		ScavTrap(const ScavTrap& src);
		ScavTrap& operator=(const ScavTrap& rhs);
		virtual ~ScavTrap();

		ScavTrap(std::string name);

		virtual void attack(const std::string& target);
		void guardGate(void);
};


#endif