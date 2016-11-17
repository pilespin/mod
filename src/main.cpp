
#include <project.hpp>
#include "Sdl.hpp"

int main()
{
	try
	{
		Sdl s = Sdl();
		s.init();

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
