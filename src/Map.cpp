
#include "Map.hpp"

Map::Map() {}

Map::Map(std::vector<Vector> point, int x, int y, int reduceFactor, float defaultAssign) {

	if (x > 0 && y > 0)
	{
		this->_val			= 0;
		this->reduceFactor	= reduceFactor;
		this->mapSizeX		= x / reduceFactor;
		this->mapSizeY		= y / reduceFactor;
		this->point = point;
		this->initMap(defaultAssign);
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
int		Map::getValue() const			{	return (this->_val);		}
int		Map::getMapSizeX() const		{	return (this->mapSizeX);	}
int		Map::getMapSizeY() const		{	return (this->mapSizeY);	}
// const std::vector<std::vecto		getMap() const		{	return (this->map);			}
float		Map::getMap(int x, int y) {

	if (x < 0 || x > this->mapSizeX - 1)
		x = this->mapSizeX - 1;
	if (y < 0 || y > this->mapSizeY - 1)
		y = this->mapSizeY - 1;

	return (this->map[x][y]);
}

///////////////////////////////////////////////////////////////////////////////

std::list<float> Map::getCosineLine(float z) {

	std::list<float> l;

	if (z <= 0)
		return (std::list<float> {0});

	for (float i = 0; i < M_PI; i += M_PI / (this->mapSizeX/4)) {
		l.push_back(mylib::ratiof(z, 1.2, (std::cos(i)/2+0.5)));
	}
	return (l);
}

void	Map::placePointOnSide(int x, int y, float z, int side) {

	std::list<float> res = getCosineLine(z);
	int i = 0;
	for (auto it = res.begin(); it != res.end(); it++) {
		if (side == 0 || side == 3)
			i++;
		else if (side == 1 || side == 2)
			i--;

		int j = 0;
		std::list<float> res2 = getCosineLine(*it);
		for (auto it2 = res2.begin(); it2 != res2.end(); it2++) {
			if (j == 0)
				assignMap(Vector(x - i, y, *it2));

			if (side == 0 || side == 1)
				j++;
			else if (side == 2 || side == 3)
				j--;
			assignMap(Vector(x - i, y - j, *it2));
		}
	}
}

void	Map::placePoint() {
	
	std::vector<float>	push;

	for (auto it = point.begin(); it != point.end(); it++) {

		int x 	= it->x / reduceFactor;
		int y 	= it->y / reduceFactor;
		float z	= it->z / reduceFactor;

		std::cout << x<< " " << y<< " "<< z<< std::endl;
		push.push_back(static_cast<float>(x));
		push.push_back(static_cast<float>(y));
		push.push_back(z);
		cuve.push_back(push);
		push.clear();

		placePointOnSide(x+1, y, z, 0);
		placePointOnSide(x-1, y, z, 1);
		placePointOnSide(x-1, y, z, 2);
		placePointOnSide(x+1, y, z, 3);
		
	}
}

float 	Map::getZMax() const{

	float maxSize	= 0;

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
void Map::getcuve()
{
	// std::vector<float>	push;

	// for (int y = 1; y != mapSizeY -1; y++)
	// {
	// 	for (int x = 1; x != mapSizeX-1 ; x++)
	// 	{
	// 		float z = this->map[x][y];

	// 		float z1 = this->map[x+1][y];
	// 		float z2 = this->map[x][y+1];
	// 		float z3 = this->map[x-1][y];
	// 		float z4 = this->map[x][y-1];
	// 		float z5 = this->map[x+1][y+1];
	// 		float z6 = this->map[x+1][y-1];
	// 		float z7 = this->map[x-1][y+1];
	// 		float z8 = this->map[x-1][y-1];

	// 		if (z > z1 && z > z2 && z > z3 && z > z4 && z > z5 && z > z6 && z > z7 && z > z8 && z > 0)
	// 		{
	// 			push.push_back(x);
	// 			push.push_back(y);
	// 			push.push_back(this->map[x][y]);
	// 			std::cout<<z<<" "<< x<< " " << y <<" a "<<std::endl;
	// 			this->cuve.push_back(push);
	// 		}

	// 	}
	// }
	// exit(0);
}

void	Map::assignMap(Vector v) {

	// if (v.x < 0 || v.x > this->mapSizeX - 1)
	// 	v.x = this->mapSizeX - 1;
	// if (v.y < 0 || v.y > this->mapSizeY - 1)
	// 	v.y = this->mapSizeY - 1;

	if (v.x >= 0 && v.y >= 0 && v.x < this->mapSizeX && v.y < this->mapSizeY)
	{
		if (this->map[v.x][v.y] < v.z)
			this->map[v.x][v.y] = v.z;
	}
	// else 
		// throw Msg("This value is out of map");
}

void	Map::initMap(float nb) {

	std::vector<std::vector<float>> vec(mapSizeX, std::vector<float>(mapSizeY));
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
			std::cout << std::setprecision(2) << this->map[x][y] << " ";
			len = mylib::intlen(this->map[x][y]);
			while (len++ < maxLen)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void	Map::empty() {

}
