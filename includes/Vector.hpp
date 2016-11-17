
#pragma once

#include <iostream>

class Vector {

public:
	Vector();
	Vector(int x, int y, int z);
	~Vector();
	Vector(Vector const &src);
	Vector &operator=(Vector const &rhs);

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
	int _val;
	int x;
	int y;
	int z;
};

std::ostream &operator<<(std::ostream &o, Vector &c);
