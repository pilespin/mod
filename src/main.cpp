
#include <project.hpp>
#include "Sdl.hpp"
#include "Map.hpp"
#include "Parse.hpp"

int main()
{
	try
	{
		Sdl 	s = Sdl();
		Parse	p = Parse();

		p.readFile("./data/demo4.mod1");
		// p.printData();

		Map		m = Map(p.getPointOfMap(), 20000, 20000, 200);
		// m.printMap();
		s.setWindowSize(1000, 1000);
		s.init(m);
		while (1)
		{
		// std::cout << "Pass" << std::endl;

			s.draw(m);
			s.getKey();

			mylib::sleep(10);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
