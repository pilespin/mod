
#pragma once

#include <project.hpp>
#include <iostream>
#include <vector>
#include <sys/time.h>

class mylib {

public:
	mylib();
	~mylib();
	// mylib(mylib const &src);
	// mylib &operator=(mylib const &rhs);

///////////////////////////////////////////////////////////////////////////////
	int			getValue() const;
	void		empty();
///////////////////////////////////////////////////////////////////////////////

	static void							sleep(int ms);
	static int							ratio(int maxVal1, int maxVal2, int yourVal);
	static std::list<std::string>		split(std::string str);
	static std::string 					trim(std::string str);
	static int							intlen(int x);
	static double	 					utime();

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

std::ostream &operator<<(std::ostream &o, mylib &c);
