
#include <project.hpp>

// void 	Map::change_point(int x, int y, int z, double a, double h, double it, int x_inc, int y_inc)
// {
// 	//std::cout<<x<<"  " << y << "  "<< it<<std::endl; 
// 	if (x < MAX_SIZE && x >= 0)
// 	{
// 		if (y < MAX_SIZE && y >= 0)
// 		{
// 			if (map[x][y] < h)
// 			{
// 				map[x][y] = h;
// 			}
			
// 		}
// 	}
// }
	double  Map::access(int x, int y)
	{
		return this->map[x][y];
	}


void 	Map::incre_point_next(double xo, double yo, double zo , double a, double it)
{
	double x;
	double y;
	double  nd;

	(void)it;
	x = 0;
	while (x < MAX_SIZE)
	{
		y = 0;
		while (y < MAX_SIZE)
		{
			
			nd  = sqrt(pow(x - xo, 2) + pow(y - yo, 2));
			double h = static_cast<double>(nd * nd) * a + zo;
			printf("%lf  ", h);
			if (this->map[static_cast<int>(x)][static_cast<int>(y)] < h)
				this->map[static_cast<int>(x)][static_cast<int>(y)] = h;
			// if (h < MAX_SIZE / 3.0)
			// 	s.draw_pixel(x,y, 0,0,255);
			// if (h < MAX_SIZE / 2.0)
			// 	s.draw_pixel(x,y, 0,255,0);
			// else
			// 	s.draw_pixel(x,y, 255,0,0);
			y++;
		}
		printf("\n");
		x++;
	}
}

Map::Map(Parse param) 		{	

	int i = 0;
	std::vector<double> v;

	while (i < MAX_SIZE)
	{
		v.push_back(0.0);
		i++;
	}
	i = 0;
	while (i < MAX_SIZE)
	{
		this->map.push_back(v);
		i++;
	}
	//double c = 0;
	
	double a = -static_cast<double>(MAX_SIZE) / (static_cast<double>(SIZE_TO_SEA) * static_cast<double>(SIZE_TO_SEA));
	printf("%lf  %lf\n", a, 0.008);

	i = 0;
	double l= 0.0;
	while ( l < 250.0)
	{
		double res = a * l * l + MAX_SIZE;
		printf("%lf  %lf\n", res, 0.008);
		l++;
	}
	std::cout<< "as: " << param.size() << std::endl;;
	while (i < param.size())
	{
		double a = -static_cast<double>(param[i].z) / (static_cast<double>(SIZE_TO_SEA) * static_cast<double>(SIZE_TO_SEA));
		int x = param[i].x;
		int y = param[i].y;
		int z = param[i].z;
		incre_point_next(x,y,z,a, 1);
		this->put_map();
		i++;
	}
}

Map::Map() 		{	

	int i = 0;
	std::vector<double> v;

	while (i < MAX_SIZE)
	{
		v.push_back(0.0);
		i++;
	}
	i = 0;
	while (i < MAX_SIZE)
	{
		this->map.push_back(v);
		i++;
	}
	double a = MAX_SIZE / ((MAX_SIZE/2.0) * (MAX_SIZE/2.0));
	printf("%lf  %lf\n", a, 0.008);

}

void	Map::put_map()
{
	int x = 0;
	int y = 0 ;

	while (x < MAX_SIZE)
	{
		y = 0;
		while (y  < MAX_SIZE)
			std::cout<<this->map[x][y++];
		std::cout <<std::endl;
		x++;
	}
}

Map::~Map()	{

}

Map::Map(Map const &src)	{	
	this->_val = src._val;
	this->map = src.map;
}

Map	&Map::operator=(Map const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
		this->map = rhs.map;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Map &c) {
	o << "I'm Map class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Map::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////
void	Map::empty() {

}
