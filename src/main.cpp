
#include <project.hpp>


int main()
{
	try
	{
		Sdl 	s = Sdl();
		Parse	p = Parse();

		s.init();
		p.readFile("./data/demo1.mod1");
		p.printData();
		Map		map(p);		
		map.put_map();

		while (1)
		{
			s.draw(map);
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
