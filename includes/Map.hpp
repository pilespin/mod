
#pragma once

class Parse;

class Map {

public:
	Map(Parse param);
	Map();
	~Map();
	Map(Map const &src);
	Map &operator=(Map const &rhs);
	double access(int x, int y);
	int			getValue() const;
	void		empty();
	void		put_map();

	///////////////////////////// EXCEPTION ///////////////////////////////////
	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};
	///////////////////////////////////////////////////////////////////////////
private:
// void 	change_point(int x, int y, int z, double a, double h, double it);
void 	incre_point_next(double xo, double yo, double zo , double a, double it);
	std::vector<std::vector<double>> map;
	int _val;
};

std::ostream &operator<<(std::ostream &o, Map &c);
