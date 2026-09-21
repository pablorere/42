#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void) {
	std::srand(std::time(NULL));
	std::cout << "===== ex02 AForm =====" << std::endl;

	Bureaucrat clerk("Clerk", 130);
	Bureaucrat boss("Boss", 1);
	ShrubberyCreationForm shrub("home");
	RobotomyRequestForm robot("Bender");
	PresidentialPardonForm pardon("Arthur Dent");

	std::cout << "\n[1] the three concrete forms" << std::endl;
	std::cout << "    " << shrub << std::endl;
	std::cout << "    " << robot << std::endl;
	std::cout << "    " << pardon << std::endl;

	std::cout << "\n[2] executing a form that is not signed" << std::endl;
	boss.executeForm(pardon);

	std::cout << "\n[3] executing with a grade that is not high enough" << std::endl;
	boss.signForm(pardon);
	clerk.executeForm(pardon);

	std::cout << "\n[4] shrubbery creation (writes home_shrubbery)" << std::endl;
	clerk.signForm(shrub);
	clerk.executeForm(shrub);

	std::cout << "\n[5] robotomy request (50% success)" << std::endl;
	boss.signForm(robot);
	boss.executeForm(robot);
	boss.executeForm(robot);
	boss.executeForm(robot);

	std::cout << "\n[6] presidential pardon" << std::endl;
	boss.executeForm(pardon);

	std::cout << "\n[7] polymorphism: execute through an AForm pointer" << std::endl;
	AForm *base = &robot;
	boss.executeForm(*base);

	std::cout << "\n===== done =====" << std::endl;
	return (0);
}
