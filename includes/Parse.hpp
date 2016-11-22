
#pragma once

#include <project.hpp>
#include "Vector.hpp"

#define REGEX_GET_ALL "\\(\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*\\)"

class Parse {

public:
	Parse();
	~Parse();
	Parse(Parse const &src);
	Parse &operator=(Parse const &rhs);
	Vector	operator[](int it);		
	int			getValue() const;
	void		empty();
	int			size() const ;

	void 		parseLine(std::string line);
	void		closeFile();
	void		readFile(std::string filename);

	void		printData();

	///////////////////////////// EXCEPTION ///////////////////////////////////
	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

private:
	void		openFile(std::string filename);

	int _val;
	std::ifstream 		file;
	std::vector<Vector> vector;

};

std::ostream &operator<<(std::ostream &o, Parse &c);
