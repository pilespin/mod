
#pragma once

#include <project.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

class Sfml {

public:
	Sfml();
	~Sfml();
	Sfml(Sfml const &src);
	Sfml &operator=(Sfml const &rhs);

	int			getValue() const;
	void		empty();
	void		draw();
	void		getKey();
	void		init();

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
	sf::RenderWindow window;
};

std::ostream &operator<<(std::ostream &o, Sfml &c);
