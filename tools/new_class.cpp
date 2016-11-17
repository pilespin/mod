
#include "NewName.hpp"

NewName::NewName() 						{	this->_val = 0;	}

NewName::~NewName()						{}

NewName::NewName(NewName const &src)	{	
	this->_val = src._val;
}

NewName	&NewName::operator=(NewName const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, NewName &c) {
	o << "I'm NewName class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		NewName::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////
void	NewName::empty() {

}
