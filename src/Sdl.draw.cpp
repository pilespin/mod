
#include <project.hpp>
#include "Sdl.hpp"

void	Sdl::preparateLand(Map m) {

	int maxZ = m.getZMax();

	listLAND = glGenLists(1);
	listLANDSize = 0;
	glNewList(listLAND, GL_COMPILE);
	glBegin(GL_QUADS);
	for (float y = m.getMapSizeY(); y != 0; y--)
	{
		for (float x = m.getMapSizeX(); x != 0; x--)
		{
			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y)), 0);
			glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y)), 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y+1)), 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y+1)), 0);
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1)/m.getMapSizeX() );
			listLANDSize++;
		}
	}
	glEnd();
	glEndList();
}

void	Sdl::drawWater(Map m) {

	glBegin(GL_QUADS);
	for (float y = m.getMapSizeY(); y != 0; y--)
	{
		for (float x = m.getMapSizeX(); x != 0; x--)
		{
			glColor4f(0, 250, 250, 0.6);
			glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y) );
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y) );
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1) );
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1) );
		}
	}
	glEnd();
}

void	Sdl::drawRain(Map &m, Map l) {
	(void)l;
	int x = mylib::getRandomNumber(m.getMapSizeX());
	int y = mylib::getRandomNumber(m.getMapSizeX());

	float dt = 0.001;
	float add = dt/(m.getMapSizeX()/4);
	if (m.getMap(x,y) > l.getMap(x,y))
		m.assignMap(Vector(x, y, m.getMap(x,y)/m.getMapSizeX() + add));
	else
		m.assignMap(Vector(x, y, l.getMap(x,y)/m.getMapSizeX() + add));

		// for (float t = 0; t != 5; t++) {

	for (float y = 0; y != m.getMapSizeY(); y++) {
		for (float x = 0; x != m.getMapSizeX(); x++) {
			// std::cout << "first : " << m.getMap(x,y) << std::endl;
			// std::cout << "second: " << l.getMap(x,y)/m.getMapSizeX() << std::endl;
			if (m.getMap(x,y) > 0)
			{
				if (m.getMap(x,y) - dt >= m.getMap(x,y+1) && m.getMap(x,y) > l.getMap(x,y+1)/m.getMapSizeX())
				{
					m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
					m.assignMap(Vector(x, y+1, m.getMap(x,y+1) + dt));
				}
				if (m.getMap(x,y) - dt >= m.getMap(x,y-1) && m.getMap(x,y) > l.getMap(x,y-1)/m.getMapSizeX())
				{
					m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
					m.assignMap(Vector(x, y-1, m.getMap(x,y-1) + dt));
				}
				if (m.getMap(x,y) - dt >= m.getMap(x+1,y) && m.getMap(x,y) > l.getMap(x+1,y)/m.getMapSizeX())
				{
					m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
					m.assignMap(Vector(x+1, y, m.getMap(x+1,y) + dt));
				}
				if (m.getMap(x,y) - dt >= m.getMap(x-1,y) && m.getMap(x,y) > l.getMap(x-1,y)/m.getMapSizeX())
				{
					m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
					m.assignMap(Vector(x-1, y, m.getMap(x-1,y) + dt));
				}
			}
		}
	}
			mylib::sleep(100);
	// }

}

void	Sdl::drawWave(Map &m, Map l) {
	(void)l;
	// static int passage = 0;
	// passage++;
	// int x = mylib::getRandomNumber(m.getMapSizeX());
	// int y = mylib::getRandomNumber(m.getMapSizeY());

	// x = 1;
	// y = 1;
	// m.assignMap(Vector(x, y, m.getMap(x,y) + 0.1));
	float dt = 0.0001;
	float add = dt/(m.getMapSizeX()/4);
	// float wav = 0.001;
	// if (passage >= m.getMapSizeX())
	// {
		// passage = 0;
	m.assignMap(Vector(1, 1, m.getMap(1, 1) + add));
	m.assignMap(Vector(1, m.getMapSizeY()-1, m.getMap(1,m.getMapSizeY()-1) + add));
	m.assignMap(Vector(m.getMapSizeX()-1, 1, m.getMap(m.getMapSizeX()-1, 1) + add));
	m.assignMap(Vector(m.getMapSizeX()-1, m.getMapSizeY()-1, m.getMap(m.getMapSizeX()-1,m.getMapSizeY()-1) + add));
	// }
	for (float t = 0; t != 5; t++) {

		for (float y = 0; y != m.getMapSizeY(); y++) {
			for (float x = 0; x != m.getMapSizeX(); x++) {
			// std::cout << "first : " << m.getMap(x,y) << std::endl;
			// std::cout << "second: " << l.getMap(x,y)/m.getMapSizeX() << std::endl;
				if (m.getMap(x,y) > 0)
				{
					if (m.getMap(x,y) - dt > m.getMap(x,y+1) && m.getMap(x,y) > l.getMap(x,y+1)/m.getMapSizeX())
					{
						m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
						m.assignMap(Vector(x, y+1, m.getMap(x,y+1) + dt));
					}
					if (m.getMap(x,y) - dt > m.getMap(x,y-1) && m.getMap(x,y) > l.getMap(x,y-1)/m.getMapSizeX())
					{
						m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
						m.assignMap(Vector(x, y-1, m.getMap(x,y-1) + dt));
					}
					if (m.getMap(x,y) - dt > m.getMap(x+1,y) && m.getMap(x,y) > l.getMap(x+1,y)/m.getMapSizeX())
					{
						m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
						m.assignMap(Vector(x+1, y, m.getMap(x+1,y) + dt));
					}
					if (m.getMap(x,y) - dt > m.getMap(x-1,y) && m.getMap(x,y) > l.getMap(x-1,y)/m.getMapSizeX())
					{
						m.assignMap(Vector(x, y, m.getMap(x,y) - dt));
						m.assignMap(Vector(x-1, y, m.getMap(x-1,y) + dt));
					}
				}
			}
		}
	}
}

void	Sdl::draw(Map m) {
	(void)m;
	glClearColor(0.25f, 0.5f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

	// glMatrixMode(GL_PROJECTION);
	// glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tranX, tranY, tranZ);
	glTranslatef(0.5, 0.5, 0);
	glRotatef(rotX, 1.0, 0.0, 0.0);
	glRotatef(rotY, 0.0, 1.0, 0.0);
	glRotatef(rotZ, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, -0.5, 0);

	glCallList(listLAND);

	if (drawMode == eDrawMode::ByGround)
	{
		float tmp = 1.0*m.getZMax() / m.getMapSizeX();
		float height = mylib::ratiof(tmp, 99, waterPercent) -0.000001;
		w.initMap(height);
	}
	else if (drawMode == eDrawMode::Rain) 
	{
		drawRain(w, m);
	}
	else if (drawMode == eDrawMode::Wave) 
	{
		drawWave(w, m);
	}
	drawWater(w);

	if (m.getMapSizeX() < 20)
	{
		std::cout << "------------ MAP LAND ------------" << std::endl;
		m.printMap();
		std::cout << "------------ MAP WATER ------------" << std::endl;
		w.printMap();
	}

	glPopMatrix();

	SDL_RenderPresent(renderer);
}
