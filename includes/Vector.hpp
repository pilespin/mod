
#pragma once

#include <iostream>

class Vector {

public:
	Vector(int x, int y, float z);
	~Vector();
	// Vector(Vector const &src);
	// Vector &operator=(Vector const &rhs);

	int			getValue() const;
	void		empty();

	///////////////////////////// EXCEPTION ///////////////////////////////////
	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

public:
	Vector();
	int _val;
	int x;
	int y;
	float z;
};

std::ostream &operator<<(std::ostream &o, Vector &c);
