#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _is_signed(false), _sign_grade(150), _execute_grade(150) {}

AForm::AForm(const std::string &name, int sign_grade, int execute_grade)
	: _name(name), _is_signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade) {
	checkGrade(_sign_grade);
	checkGrade(_execute_grade);
}

AForm::AForm(const AForm &other)
	: _name(other._name), _is_signed(other._is_signed),
	  _sign_grade(other._sign_grade), _execute_grade(other._execute_grade) {}

AForm &AForm::operator=(const AForm &other) {
	if (this != &other)
		_is_signed = other._is_signed;
	return (*this);
}

AForm::~AForm() {}

void AForm::checkGrade(int grade) {
	if (grade < 1 || grade > 150)
		grade < 1 ? throw GradeTooHighException() : throw GradeTooLowException();
}

const std::string &AForm::getName() const { return (_name); }

bool AForm::getIsSigned() const { return (_is_signed); }

int AForm::getSignGrade() const { return (_sign_grade); }

int AForm::getExecuteGrade() const { return (_execute_grade); }

void AForm::beSigned(const Bureaucrat &b) {
	if (b.getGrade() > _sign_grade)
		throw GradeTooLowException();
	_is_signed = true;
}

void AForm::execute(const Bureaucrat &executor) const {
	if (!_is_signed)
		throw NotSignedException();
	if (executor.getGrade() > _execute_grade)
		throw GradeTooLowException();
	executeAction();
}

const char *AForm::GradeTooHighException::what() const throw() { return ("AForm grade too high!"); }

const char *AForm::GradeTooLowException::what() const throw() { return ("AForm grade too low!"); }

const char *AForm::NotSignedException::what() const throw() { return ("AForm is not signed!"); }

std::ostream &operator<<(std::ostream &out, const AForm &f) {
	return (out << "AForm \"" << f.getName() << "\" (sign " << f.getSignGrade()
		<< ", exec " << f.getExecuteGrade() << ") is "
		<< (f.getIsSigned() ? "signed" : "not signed") << ".");
}
