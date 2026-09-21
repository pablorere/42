#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main(void) {
	std::cout << "===== ex01 Form =====" << std::endl;
	Bureaucrat intern("Intern", 100);
	Bureaucrat boss("Boss", 1);

	std::cout << "\n[1] default state" << std::endl;
	Form review("Review", 50, 25);
	std::cout << "    " << review << std::endl;

	std::cout << "\n[2] invalid grades" << std::endl;
	try { Form bad("Bad", 0, 42); } catch (std::exception &e) {
		std::cout << "    sign 0   : " << e.what() << std::endl;
	}
	try { Form bad("Bad", 151, 42); } catch (std::exception &e) {
		std::cout << "    sign 151 : " << e.what() << std::endl;
	}
	try { Form bad("Bad", 42, 0); } catch (std::exception &e) {
		std::cout << "    exec 0   : " << e.what() << std::endl;
	}

	std::cout << "\n[3] signForm with grade too low (intern 100 needs 50)" << std::endl;
	intern.signForm(review);
	std::cout << "    " << review << std::endl;

	std::cout << "\n[4] signForm with grade high enough (boss 1)" << std::endl;
	boss.signForm(review);
	std::cout << "    " << review << std::endl;

	std::cout << "\n[5] beSigned called directly" << std::endl;
	Form direct("Direct", 1, 1);
	try { direct.beSigned(intern); } catch (std::exception &e) {
		std::cout << "    caught    : " << e.what() << std::endl;
	}
	boss.signForm(direct);
	std::cout << "    " << direct << std::endl;

	std::cout << "\n[6] copy constructor / assignment" << std::endl;
	Form copy(direct);
	Form target("Target", 100, 100);
	target = direct;
	std::cout << "    original  : " << direct << std::endl;
	std::cout << "    copy      : " << copy << std::endl;
	std::cout << "    assigned  : " << target << " (name stays Target)" << std::endl;

	std::cout << "\n===== done =====" << std::endl;
	return (0);
}
