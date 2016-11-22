
#include "Parse.hpp"
#include "Vector.hpp"

Parse::Parse() 						{	this->_val = 0;	}

Parse::~Parse()						{}

Parse::Parse(Parse const &src)	{	
	this->_val = src._val;
	this->vector =src.vector;
}

Vector Parse::operator[](int it) {
	return this->vector[it];

}
int Parse::size()const 
{
	std::cout<<this->vector.size()<<std::endl;
	return (static_cast<int>(this->vector.size()));
}

Parse	&Parse::operator=(Parse const &rhs) {

	if (this != &rhs)
	{
		this->vector = rhs.vector;
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Parse &c) {
	o << "I'm Parse class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Parse::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////

void	Parse::parseLine(std::string line) {

	// std::cout << "line: " << line << std::endl;

	std::smatch res;

	std::regex r(REGEX_GET_ALL);
	if (std::regex_search(line, res, r))
	{
		for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r);
			i != std::sregex_iterator();
			++i )
		{
			res = *i;
			// std::cout << "regex: " << res[1] << "," << res[2] << "," << res[3] << std::endl;
			// if (std::is_numeric(res[1]))
			this->vector.push_back(Vector(std::stoi(res[1])*MAX_SIZE/ECHELLE, std::stoi(res[2])*MAX_SIZE/ECHELLE, std::stoi(res[3])*MAX_SIZE/ECHELLE));
		}
	}
}

////////////////////////////////////// PRINT //////////////////////////////////

void	Parse::printData() {

	std::cout << "---------------------" << std::endl;
	std::cout << "Vector:" << this->vector.size()<< std::endl;
	for (auto it = this->vector.begin(); it != this->vector.end(); it++) {
		std::cout << "Vector: x: " << it->x << " y: " << it->y << " z: " << it->z << std::endl;
	}
	std::cout << "---------------------" << std::endl;
}


////////////////////////////////////// IO /////////////////////////////////////

void	Parse::openFile(std::string filename) {

	this->file.open(filename);
	if (!this->file.is_open())
	{
		throw Msg("Error: Unable to open file " + filename);
	}
}

void	Parse::closeFile() {
	if (this->file.is_open())
		this->file.close();
}

void	Parse::readFile(std::string filename) {

	if (filename.length())
		openFile(filename);

	std::string line;

	if (this->file.is_open())
	{
		while (getline(this->file, line))
		{
			if (line.length())
			{
				this->parseLine(line);
			}
		}
		closeFile();
	}
	else
		throw Msg("Error: Unable to open file " + filename);
}

//////////////////////////////////// ELSE /////////////////////////////////////

void	Parse::empty() {

}
