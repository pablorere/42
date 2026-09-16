#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() {
    this->_fixed = 0;
}

Fixed::Fixed(const int val) {
    this->_fixed = val << this->fract;
}

Fixed::Fixed(const float val) {
    this->_fixed = roundf(val * (1 << this->fract));
}

Fixed::Fixed(const Fixed &fixed) {
    *this = fixed;
}

Fixed &Fixed::operator=(const Fixed &fixed) {
    this->_fixed = fixed.getRawBits();
    return *this;
}

Fixed::~Fixed() {
}

float Fixed::toFloat(void) const {
    return (float)this->_fixed / (1 << this->fract);
}

int Fixed::toInt(void) const {
    return this->_fixed >> this->fract;
}

int Fixed::getRawBits(void) const {
    return this->_fixed;
}

void Fixed::setRawBits(int const raw) {
    this->_fixed = raw;
}

// Comparison operators
bool Fixed::operator>(const Fixed &fixed) const {
    return this->_fixed > fixed._fixed;
}

bool Fixed::operator<(const Fixed &fixed) const {
    return this->_fixed < fixed._fixed;
}

bool Fixed::operator>=(const Fixed &fixed) const {
    return this->_fixed >= fixed._fixed;
}

bool Fixed::operator<=(const Fixed &fixed) const {
    return this->_fixed <= fixed._fixed;
}

bool Fixed::operator==(const Fixed &fixed) const {
    return this->_fixed == fixed._fixed;
}

bool Fixed::operator!=(const Fixed &fixed) const {
    return this->_fixed != fixed._fixed;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &fixed) const {
    return Fixed(this->toFloat() + fixed.toFloat());
}

Fixed Fixed::operator-(const Fixed &fixed) const {
    return Fixed(this->toFloat() - fixed.toFloat());
}

Fixed Fixed::operator*(const Fixed &fixed) const {
    return Fixed(this->toFloat() * fixed.toFloat());
}

Fixed Fixed::operator/(const Fixed &fixed) const {
    return Fixed(this->toFloat() / fixed.toFloat());
}

// Increment/Decrement operators
Fixed &Fixed::operator++(void) {
    this->_fixed++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed tmp(*this);
    this->_fixed++;
    return tmp;
}

Fixed &Fixed::operator--(void) {
    this->_fixed--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed tmp(*this);
    this->_fixed--;
    return tmp;
}

// Static min/max functions
Fixed &Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
    os << fixed.toFloat();
    return os;
}
