#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

static AForm *makeShrubbery(const std::string &target) { return (new ShrubberyCreationForm(target)); }

static AForm *makeRobotomy(const std::string &target) { return (new RobotomyRequestForm(target)); }

static AForm *makePardon(const std::string &target) { return (new PresidentialPardonForm(target)); }

typedef AForm *(*t_make)(const std::string &);

struct FormEntry {
	const char *name;
	t_make make;
};

static const FormEntry g_forms[] = {
	{ "shrubbery creation", makeShrubbery },
	{ "robotomy request", makeRobotomy },
	{ "presidential pardon", makePardon }
};

Intern::Intern() {}

Intern::Intern(const Intern &) {}

Intern &Intern::operator=(const Intern &) { return (*this); }

Intern::~Intern() {}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const {
	for (int i = 0; i < 3; ++i) {
		if (name == g_forms[i].name) {
			std::cout << "Intern creates " << name << std::endl;
			return (g_forms[i].make(target));
		}
	}
	std::cout << "Intern cannot create " << name << ": unknown form name" << std::endl;
	return (NULL);
}
