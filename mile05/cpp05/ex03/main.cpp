#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main(void) {
	std::cout << "===== ex03 Intern =====" << std::endl;
	Intern intern;
	Bureaucrat boss("Boss", 1);

	std::cout << "\n[1] makeForm for every known form" << std::endl;
	AForm *shrub = intern.makeForm("shrubbery creation", "garden");
	AForm *robot = intern.makeForm("robotomy request", "Bender");
	AForm *pardon = intern.makeForm("presidential pardon", "Arthur Dent");
	std::cout << "    " << *shrub << std::endl;
	std::cout << "    " << *robot << std::endl;
	std::cout << "    " << *pardon << std::endl;

	std::cout << "\n[2] unknown form name" << std::endl;
	AForm *unknown = intern.makeForm("coffee making", "nobody");
	std::cout << "    returned pointer is " << (unknown ? "valid (WRONG)" : "NULL") << std::endl;

	std::cout << "\n[3] signing and executing the created forms" << std::endl;
	boss.signForm(*shrub);
	boss.executeForm(*shrub);
	boss.signForm(*robot);
	boss.executeForm(*robot);
	boss.signForm(*pardon);
	boss.executeForm(*pardon);

	std::cout << "\n[4] cleanup (the caller owns the pointers)" << std::endl;
	delete shrub;
	delete robot;
	delete pardon;
	std::cout << "    deleted shrub, robot and pardon" << std::endl;

	std::cout << "\n===== done =====" << std::endl;
	return (0);
}
