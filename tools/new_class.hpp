
#pragma once

#include <iostream>

class NewName {

public:
	NewName();
	~NewName();
	NewName(NewName const &src);
	NewName &operator=(NewName const &rhs);

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

private:
	int _val;
};

std::ostream &operator<<(std::ostream &o, NewName &c);
