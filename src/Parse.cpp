
#include "Parse.hpp"
#include "Vector.hpp"

Parse::Parse() 						{	this->_val = 0;	}

Parse::~Parse()						{}

Parse::Parse(Parse const &src)	{ 
	static_cast<void>(src);
	// this->_val = src._val;
	// this->file = src.file;
	// this->vector = src.vector;
}

// Parse	&Parse::operator=(Parse const &rhs) {

// 	if (this != &rhs)
// 	{
// 		this->_val = rhs._val;
// 		// this->file = rhs.file;
// 		this->vector = rhs.vector;
// 	}
// 	return (*this);
// }

std::ostream &operator<<(std::ostream &o, Parse &c) {
	o << "I'm Parse class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int					Parse::getValue() const		{	return (this->_val);	}
std::vector<Vector>	Parse::getPointOfMap() 		{	return (this->vector);	}
///////////////////////////////////////////////////////////////////////////////

void	Parse::parseLine(std::string line) {

	std::smatch res;

	std::regex r(REGEX_GET_ALL);
	if (std::regex_search(line, res, r))
	{
		for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r);
			i != std::sregex_iterator();
			++i )
		{
			res = *i;
			this->vector.push_back(Vector(std::stoi(res[1]), std::stoi(res[2]), std::stoi(res[3])));
		}
	}
}

////////////////////////////////////// PRINT //////////////////////////////////

void	Parse::printData() {

	std::cout << "---------------------" << std::endl;
	std::cout << "Vector:" << std::endl;
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
