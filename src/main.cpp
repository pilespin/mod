
#include <project.hpp>
#include "Map.hpp"
#include "Sdl.hpp"
#include "Sfml.hpp"
#include "Parse.hpp"

int main()
{
	try
	{
		// Sdl 	s = Sdl();
		Sfml 	sf = Sfml();
		Parse	p = Parse();

		// s.init();
		sf.init();

		p.readFile("./data/demo4.mod1");
		p.printData();
		Map		map(p);		
		map.put_map();

		while (1)
		{
			// sf.draw();
			// sf.getKey();

			sf.draw(map);
			sf.getKey();

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
