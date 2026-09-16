#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap 
{
	public:
		FragTrap(void);
		FragTrap(const FragTrap& src);
		FragTrap& operator=(const FragTrap& rhs);
		virtual ~FragTrap();

		FragTrap(std::string name);

		void	highFivesGuys( void );
};

#endif