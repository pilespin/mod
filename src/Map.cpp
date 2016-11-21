
#include "Map.hpp"

Map::Map() {}

Map::Map(std::vector<Vector> point, int x, int y, int reduceFactor) {

	if (x > 0 && y > 0)
	{
		this->_val			= 0;
		this->reduceFactor	= reduceFactor;
		this->mapSizeX		= x / reduceFactor;
		this->mapSizeY		= y / reduceFactor;
		this->point = point;
		this->initMap(0);
		this->placePoint();	
	}
	else
		throw Msg("Size must be positive.");
}

Map::~Map()					{}

// Map::Map(Map const &src)	{	
// 	this->_val = src._val;
// }

// Map	&Map::operator=(Map const &rhs) {

// 	if (this != &rhs)
// 	{
// 		this->_val = rhs._val;
// 	}
// 	return (*this);
// }

std::ostream &operator<<(std::ostream &o, Map &c) {
	o << "I'm Map class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int									Map::getValue() const		{	return (this->_val);		}
int									Map::getMapSizeX() const	{	return (this->mapSizeX);	}
int									Map::getMapSizeY() const	{	return (this->mapSizeY);	}
const std::vector<std::vector<int>>	&Map::getMap() const		{	return (this->map);			}
///////////////////////////////////////////////////////////////////////////////

void	Map::placePoint() {
	int x;
	int y;
	int z;
	int i;
	int j;

	for (auto it = point.begin(); it != point.end(); it++) {

		//UPLEFT
		z = it->z / reduceFactor;
		assignMap(Vector(it->x / reduceFactor, it->y / reduceFactor, z));
		for (i = z; i != 0; i--) {

			x = it->x / reduceFactor - i;
			y = it->y / reduceFactor;

			assignMap(Vector(x + i, y - i, z - i));

			for (j = x; j != 0; j--) {
				assignMap(Vector(x, y - j + 1, z - i - j + 1));
			}
		}

		//UPRIGHT
		z = it->z / reduceFactor;
		assignMap(Vector(it->x / reduceFactor, it->y / reduceFactor, z));
		for (i = z; i != 0; i--) {

			x = it->x / reduceFactor + i;
			y = it->y / reduceFactor;

				// assignMap(Vector(x, y + i, z - i));

			for (j = x; j != 0; j--) {
				assignMap(Vector(x, y - j + 1, z - i - j + 1));
			}
		}

		//DOWNLEFT
		z = it->z / reduceFactor;
		assignMap(Vector(it->x / reduceFactor, it->y / reduceFactor, z));
		for (i = z; i != 0; i--) {

			x = it->x / reduceFactor + i;
			y = it->y / reduceFactor;

			assignMap(Vector(x - i, y + i, z - i));

			for (j = x; j != 0; j--) {
				assignMap(Vector(x, y + j, z - i - j));
			}
		}

		//DOWNRIGHT
		z = it->z / reduceFactor;
		assignMap(Vector(it->x / reduceFactor, it->y / reduceFactor, z));
		for (i = z; i != 0; i--) {

			x = it->x / reduceFactor - i;
			y = it->y / reduceFactor;

				// assignMap(Vector(x + i, y - i, z - i));

			for (j = x; j != 0; j--) {
				assignMap(Vector(x, y + j, z - i - j));
			}
		}
	}

}

int 	Map::getZMax() const{

	int maxSize	= 0;

	for (int y = 0; y != mapSizeY; y++)
	{
		for (int x = 0; x != mapSizeX; x++)
		{
			if (this->map[x][y] > maxSize)
				maxSize = this->map[x][y];
		}
	}
	return (maxSize);
}


void	Map::assignMap(Vector v) {

	if (v.x >= 0 && v.y >= 0 && v.x < this->mapSizeX && v.y < this->mapSizeY)
	{
		if (this->map[v.x][v.y] < v.z)
			this->map[v.x][v.y] = v.z;
	}
	// else 
		// throw Msg("This value is out of map");
}

void	Map::initMap(int nb) {

	std::vector<std::vector<int>> vec(mapSizeX, std::vector<int>(mapSizeY));
	this->map = vec;

	for (int y = 0; y != mapSizeY; y++)
	{
		this->map[y].assign(mapSizeX, nb);
	}
}

void	Map::printMap() {

	int maxLen 	= 0;
	int len 	= 0;

	for (int y = 0; y != mapSizeY; y++)
	{
		for (int x = 0; x != mapSizeX; x++)
		{
			if (mylib::intlen(this->map[x][y]) > maxLen)
				maxLen = mylib::intlen(this->map[x][y]);
		}
	}

	for (int y = 0; y != mapSizeY; y++)
	{
		for (int x = 0; x != mapSizeX; x++)
		{
			std::cout << this->map[x][y] << " ";
			len = mylib::intlen(this->map[x][y]);
			while (len++ < maxLen)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void	Map::empty() {

}
