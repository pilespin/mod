
#include <project.hpp>
#include "Sdl.hpp"
#include "Parse.hpp"

int main()
{
	try
	{
		Sdl 	s = Sdl();
		Parse	p = Parse();

		s.init();
		p.readFile("./data/demo5.mod1");
		p.printData();

		while (1)
		{
			s.draw();
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
