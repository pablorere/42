#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2 &copy) : x(copy.x), y(copy.y) {}

vect2 &vect2::operator=(const vect2 &copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
	}
	return (*this);
}

vect2::~vect2() {}

int &vect2::operator[](int i)
{
	return (i == 0 ? x : y);
}

int vect2::operator[](int i) const
{
	return (i == 0 ? x : y);
}

vect2 &vect2::operator++()
{
	x++;
	y++;
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 tmp = *this;
	x++;
	y++;
	return (tmp);
}

vect2 &vect2::operator--()
{
	x--;
	y--;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 tmp = *this;
	x--;
	y--;
	return (tmp);
}

vect2 &vect2::operator+=(const vect2 &v)
{
	x += v.x;
	y += v.y;
	return (*this);
}

vect2 &vect2::operator-=(const vect2 &v)
{
	x -= v.x;
	y -= v.y;
	return (*this);
}

vect2 &vect2::operator*=(int s)
{
	x *= s;
	y *= s;
	return (*this);
}

vect2 vect2::operator+(const vect2 &v) const
{
	return (vect2(x + v.x, y + v.y));
}

vect2 vect2::operator-(const vect2 &v) const
{
	return (vect2(x - v.x, y - v.y));
}

vect2 vect2::operator*(int s) const
{
	return (vect2(x * s, y * s));
}

vect2 vect2::operator-() const
{
	return (vect2(-x, -y));
}

bool vect2::operator==(const vect2 &v) const
{
	return (x == v.x && y == v.y);
}

bool vect2::operator!=(const vect2 &v) const
{
	return (!(*this == v));
}

vect2 operator*(int s, const vect2 &v)
{
	return (vect2(v[0] * s, v[1] * s));
}

std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
	os << "{" << v[0] << ", " << v[1] << "}";
	return (os);
}
