#include "Bureaucrat.hpp"
#include <iostream>

int main(void) {
	std::cout << "===== ex00 Bureaucrat =====" << std::endl;

	Bureaucrat def;
	std::cout << "\n[1] default constructor : " << def << std::endl;

	std::cout << "\n[2] incrementGrade / decrementGrade" << std::endl;
	try {
		Bureaucrat bob("Bob", 2);
		std::cout << "    start     : " << bob << std::endl;
		bob.decrementGrade();
		std::cout << "    decrement : " << bob << std::endl;
		bob.incrementGrade();
		std::cout << "    increment : " << bob << std::endl;
		bob.incrementGrade();
		std::cout << "    increment : " << bob << std::endl;
		bob.incrementGrade();
	} catch (std::exception &e) {
		std::cout << "    caught    : " << e.what() << std::endl;
	}

	std::cout << "\n[3] invalid grades" << std::endl;
	try { Bureaucrat bad("Bad", 0); } catch (std::exception &e) {
		std::cout << "    grade 0   : " << e.what() << std::endl;
	}
	try { Bureaucrat bad("Bad", 151); } catch (std::exception &e) {
		std::cout << "    grade 151 : " << e.what() << std::endl;
	}
	try {
		Bureaucrat low("Low", 150);
		low.decrementGrade();
	} catch (std::exception &e) {
		std::cout << "    dec 150   : " << e.what() << std::endl;
	}

	std::cout << "\n[4] copy constructor / assignment" << std::endl;
	Bureaucrat alice("Alice", 42);
	Bureaucrat copy(alice);
	Bureaucrat assigned;
	assigned = alice;
	Bureaucrat *ptr = &alice;
	alice = *ptr;
	std::cout << "    original  : " << alice << std::endl;
	std::cout << "    copy      : " << copy << std::endl;
	std::cout << "    assigned  : " << assigned << " (name stays default)" << std::endl;

	std::cout << "\n===== done =====" << std::endl;
	return (0);
}
