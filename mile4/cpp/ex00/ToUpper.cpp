#include "megaphone.hpp"
ToUpper::ToUpper() : _text("* LOUD AND UNBEARABLE FEEDBACK NOISE *"){} //default

ToUpper::ToUpper(std::string text) : _text(text){} //custom

ToUpper::ToUpper(const ToUpper &other) : _text(other._text){} // copia

ToUpper &ToUpper::operator=(const ToUpper &other){ // operador
    if (this != &other)
        this->_text= other._text;
    return *this;
}

ToUpper::~ToUpper(){} // destructor

std::string ToUpper::scream(){ // metodo
    std::string temp = _text;
    for(std::size_t i = 0; i < temp.length(); i++)
    {
        temp[i] = std::toupper(_text[i]);
    }
    return(temp);
}