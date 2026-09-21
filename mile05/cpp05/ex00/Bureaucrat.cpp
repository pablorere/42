#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name), _grade(grade) {
	if (_grade < 1 || _grade > 150)
		_grade < 1 ? throw GradeTooHighException() : throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	if (this != &other)
		_grade = other._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat() {}

const std::string &Bureaucrat::getName() const { return (_name); }

int Bureaucrat::getGrade() const { return (_grade); }

void Bureaucrat::incrementGrade() { _grade == 1 ? throw GradeTooHighException() : --_grade; }

void Bureaucrat::decrementGrade() { _grade == 150 ? throw GradeTooLowException() : ++_grade; }

const char *Bureaucrat::GradeTooHighException::what() const throw() { return ("Grade too high!"); }

const char *Bureaucrat::GradeTooLowException::what() const throw() { return ("Grade too low!"); }

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b) {
	return (out << b.getName() << ", bureaucrat grade " << b.getGrade() << ".");
}

