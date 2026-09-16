#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() {
    std::cout << "Default constructor called" << std::endl;
    this->_fixed = 0;
}

Fixed::Fixed(const int val) {
    std::cout << "Int constructor called" << std::endl;
    this->_fixed = val << this->fract;
}

Fixed::Fixed(const float val) {
    std::cout << "Float constructor called" << std::endl;
    this->_fixed = roundf(val * (1 << this->fract));
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed) {
    std::cout << "Copy constructor called" << std::endl;
    *this = fixed;
}

Fixed &Fixed::operator=(const Fixed &fixed) {
    std::cout << "Copy assignment operator called" << std::endl;
    this->_fixed = fixed.getRawBits();
    return *this;
}

float Fixed::toFloat( void ) const {
    return (float)this->_fixed / (1 << this->fract);
}

int Fixed::toInt( void ) const {
    return this->_fixed >> this->fract;
}

int Fixed::getRawBits(void) const {
    return this->_fixed;
}

void Fixed::setRawBits(int const raw) {
    this->_fixed = raw;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
    os << fixed.toFloat();
    return os;
}

