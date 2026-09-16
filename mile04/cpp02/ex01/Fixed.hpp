#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>
class Fixed {
    private:
        int _fixed;
        static const int fract = 8;
    public:
        Fixed();
        Fixed(const int );
        Fixed(const float );
        ~Fixed();
        Fixed(const Fixed &fixed);
        Fixed &operator=(const Fixed &fixed);
        
        float toFloat( void ) const;
        int toInt( void ) const;
        int getRawBits(void) const;
        void setRawBits(int const raw);
}; 
std::ostream &operator<<(std::ostream &os, const Fixed &fixed);
#endif