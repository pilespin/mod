
#pragma once

#include <project.hpp>
#include "Vector.hpp"

class Map {

public:
	Map(std::vector<Vector> point, int x, int y,  int reduceFactor = 500);
	~Map();
	// Map(Map const &src);
	// Map &operator=(Map const &rhs);

	void		assignMap(Vector v);
	void 		initMap(int nb = 0);
	void 		placePoint();
	void		printMap();
	int			getValue() const;
	int			getMapSizeX() const;
	int			getMapSizeY() const;
	int 		getZMax() const;
	void		empty();
	float		getMap(int x, int y);

	std::list<float> getCosineLine(float z);

	// const std::vector<std::vector<int>>	&getMap() const;	

	///////////////////////////// EXCEPTION ///////////////////////////////////
	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

private:
	void	placePointOnSide(int x, int y, float z, int side);
	Map();

	std::vector<std::vector<float>>	map;
	std::vector<Vector>				point;

	int _val;
	int mapSizeX;
	int mapSizeY;
	int reduceFactor;

};

std::ostream &operator<<(std::ostream &o, Map &c);
