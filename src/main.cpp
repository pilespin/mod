
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


		s.init();
		p.readFile("./data/demo4.mod1");
		// p.printData();

		Map		m = Map(p.getPointOfMap(), 20000, 20000, 50);
		// m.printMap();

		while (1)
		{
		// std::cout << "Pass" << std::endl;

			s.draw(m);
			s.getKey();

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
