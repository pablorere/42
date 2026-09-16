#ifndef TOUPPER_HPP
# define TOUPPER_HPP

# include <iostream>
# include <string>
class ToUpper
{   private:
    std::string _text;
    public:
    ToUpper(); //constructor por defecto
    ToUpper(std::string text);  // parameterized constructor
    ToUpper(const ToUpper &other); // copia canonica
    ToUpper &operator=(const ToUpper &other);  // copy assignment operator
    ~ToUpper(); //destructor
    std::string scream();
};

#endif
