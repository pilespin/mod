
#include "mylib.hpp"

mylib::mylib() 						{	this->_val = 0;	}

mylib::~mylib()						{}

mylib::mylib(mylib const &src)	{
	this->_val = src._val;
}

mylib	&mylib::operator=(mylib const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, mylib &c) {
	o << "mylib: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		mylib::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////

std::list<std::string>	mylib::split(std::string str)
{
	int 		end;
	std::string	tmp;

	std::list<std::string> v;

	while (str.length())
	{
		tmp.erase();
		str = trim(str);
		end = str.find_first_of(" 	");

		if (end > -1)
		{
			tmp = str.substr(0, end);
			str = str.substr(end);
			if (tmp.length())
				v.push_back(tmp);
		}
		else
		{
			v.push_back(str);
			break;
		}
	}
	return (v);
}

int			mylib::intlen(int x)
{
	int i;

	if (x <= 0)
		x = -x;
	i = 1;
	while (x >= 10)
	{
		x /= 10;
		i++;
	}
	return (i);
}

std::string	mylib::trim(std::string str)
{
	int st;
	int end;

	st = str.find_first_not_of(" 	");
	end = str.find_last_not_of(" 	");

	if ((end > -1 && st > -1))
		return (str.substr(st, (end - st) + 1));
	else
		return ("");
}

double  	mylib::utime()
{
	int             sec;
	double          micro;
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	micro /= 1000000;
	micro += sec;
	return (micro);
}

void		mylib::empty() {

}
