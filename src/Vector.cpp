
#include "Vector.hpp"

Vector::Vector() 						{		
	this->_val = 0;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector::Vector(int x, int y, float z) 	{	
	this->_val = 0;
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::~Vector()						{}

// Vector::Vector(Vector const &src)	{	
// 	this->_val = src._val;
// 	this->x = src.x;
// 	this->y = src.y;
// 	this->z = src.z;
// }

// Vector	&Vector::operator=(Vector const &rhs) {

// 	if (this != &rhs)
// 	{
// 		this->_val = rhs._val;
// 		this->x = rhs.x;
// 		this->y = rhs.y;
// 		this->z = rhs.z;
// 	}
// 	return (*this);
// }

std::ostream &operator<<(std::ostream &o, Vector &c) {
	o << "I'm Vector class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Vector::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////
void	Vector::empty() {

}
