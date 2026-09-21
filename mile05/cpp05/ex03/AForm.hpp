#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <exception>
# include <iostream>

class Bureaucrat;

class AForm {
private:
	const std::string _name;
	bool _is_signed;
	const int _sign_grade;
	const int _execute_grade;

	static void checkGrade(int grade);

protected:
	virtual void executeAction() const = 0;

public:
	AForm();
	AForm(const std::string &name, int sign_grade, int execute_grade);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm();

	const std::string &getName() const;
	bool getIsSigned() const;
	int getSignGrade() const;
	int getExecuteGrade() const;
	void beSigned(const Bureaucrat &b);
	void execute(const Bureaucrat &executor) const;

	class GradeTooHighException : public std::exception {
	public:
		virtual const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char *what() const throw();
	};

	class NotSignedException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const AForm &f);

#endif
