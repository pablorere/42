#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>
class Fixed {
    private:
        int _fixed;
        static const int fract = 8;
    public:
        Fixed();
        ~Fixed();
        Fixed(const Fixed &fixed);
        Fixed &operator=(const Fixed &fixed);
        int getRawBits(void) const;
        void setRawBits(int const raw);
}; 
#endif