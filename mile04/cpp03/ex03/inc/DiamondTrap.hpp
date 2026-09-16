#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
	private:
		std::string Name;

	public:
		DiamondTrap(void);
		DiamondTrap(const DiamondTrap& src);
		DiamondTrap& operator=(const DiamondTrap& rhs);
		virtual ~DiamondTrap();

		DiamondTrap(std::string name);

		void attack(const std::string& target);
		void whoAmI();
};

#endif