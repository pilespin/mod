
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

void	Sdl::drawFourSide(Map m) {
	
	float x = -1;
	float y = 1;
	
	glBegin(GL_QUADS);
	for (x = 1; x != m.getMapSizeX()+1; x++)
	{
		glColor4f(0, 250, 250, 0.6);
		glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	0 );
		glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	0 );
		glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(), 		m.getMap(x+1,y+1) );
		glVertex3f( (x)/m.getMapSizeX(),	(y)/m.getMapSizeY(), 	  	m.getMap(x,y+1) );
	}

	y = m.getMapSizeY() + 1;
	for (x = 1; x != m.getMapSizeX()+1; x++)
	{
		glColor4f(0, 250, 250, 0.6);
		glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	0 );
		glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	0 );
		glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(), 		m.getMap(x+1,y+1) );
		glVertex3f( (x)/m.getMapSizeX(),	(y)/m.getMapSizeY(), 	  	m.getMap(x,y+1) );
	}

	x = 1;
	for (y = 1; y != m.getMapSizeY()+1; y++)
	{
		glColor4f(0, 250, 250, 0.6);
		glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	0 );
		glVertex3f( (x)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(),      	0 );
		glVertex3f( (x)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1) );
		glVertex3f( (x)/m.getMapSizeX(),	(y)/m.getMapSizeY(), 	  	m.getMap(x,y+1) );
	}

	x = m.getMapSizeX() + 1;
	for (y = 1; y != m.getMapSizeY()+1; y++)
	{
		glColor4f(0, 250, 250, 0.6);
		glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	0 );
		glVertex3f( (x)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(),      	0 );
		glVertex3f( (x)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1) );
		glVertex3f( (x)/m.getMapSizeX(),	(y)/m.getMapSizeY(), 	  	m.getMap(x,y+1) );
	}
	glEnd();
}

void	Sdl::drawWater(Map m, Map l) {

	drawFourSide(m);

	float tmp = 0;
	float dt = 0.5;
	glBegin(GL_QUADS);
	for (float y = m.getMapSizeY(); y != 0; y--)
	{
		for (float x = m.getMapSizeX(); x != 0; x--)
		{
			tmp = 0.5+mylib::ratiof(dt ,LANDMaxZ, m.getMap(x,y) - l.getMap(x,y)/m.getMapSizeX());
			glColor4f(0, 200, 200, tmp);
			glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y) );
			tmp = 0.5+mylib::ratiof(dt ,LANDMaxZ, m.getMap(x+1,y) - l.getMap(x+1,y)/m.getMapSizeX());
			glColor4f(0, 200, 200, tmp);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y) );
			tmp = 0.5+mylib::ratiof(dt ,LANDMaxZ, m.getMap(x+1,y+1) - l.getMap(x+1,y+1)/m.getMapSizeX());
			glColor4f(0, 200, 200, tmp);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1) );
			tmp = 0.5+mylib::ratiof(dt ,LANDMaxZ, m.getMap(x,y+1) - l.getMap(x,y+1)/m.getMapSizeX());
			glColor4f(0, 200, 200, tmp);
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1) );
		}
	}
	glEnd();
}

void	Sdl::drawRain(Map &m, Map l) {
	(void)l;
	int x = mylib::getRandomNumber(m.getMapSizeX());
	int y = mylib::getRandomNumber(m.getMapSizeX());

	// x = m.getMapSizeX()/2;
	// y = m.getMapSizeX()/2;

	float dt = 0.001;
	float add = dt/(m.getMapSizeX()/4);
	if (m.getMap(x,y) > l.getMap(x,y))
		m.assignMap(Vector(x, y, m.getMap(x,y)/m.getMapSizeX() + add));
	else
		m.assignMap(Vector(x, y, l.getMap(x,y)/m.getMapSizeX() + add));

		// for (float t = 0; t != 5; t++) {

	drainWater(m, l);
	// mylib::sleep(1);
	// }

}

void	Sdl::drainWater(Map &m, Map l) {
	
	float dt = 0.0001;

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
	// m.assignMap(Vector(1, m.getMapSizeY()-1, m.getMap(1,m.getMapSizeY()-1) + add));
	// m.assignMap(Vector(m.getMapSizeX()-1, 1, m.getMap(m.getMapSizeX()-1, 1) + add));
	// m.assignMap(Vector(m.getMapSizeX()-1, m.getMapSizeY()-1, m.getMap(m.getMapSizeX()-1,m.getMapSizeY()-1) + add));
	// }
	drainWater(m, l);
}

void	Sdl::calcFps() {
	double new_time = mylib::utime();
	fps = 1 / (new_time - lastTime);
	lastTime = new_time;
}

void	Sdl::printFps() {

	static int t = time(NULL); 

	if (std::time(NULL) > t)
	{
		t = time(NULL);
		std::cout << fps << " FPS" << std::endl;
	}
}

void	Sdl::draw(Map m) {
	(void)m;
	
	calcFps();
	printFps();

	glClearColor(0, 0, 0, 0);
	// glClearColor(0.25f, 0.5f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

	// glMatrixMode(GL_PROJECTION);
	// glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glScalef(scaleX ,scaleY, scaleZ);
	glTranslatef(tranX, tranY, tranZ);
	glTranslatef(0.5, 0.5, 0);
	glRotatef(rotX, 1.0, 0.0, 0.0);
	glRotatef(rotY, 0.0, 1.0, 0.0);
	glRotatef(rotZ, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, -0.5, 0);

	glCallList(listLAND);

	if (drawMode == eDrawMode::ByGround)
	{
		float height = mylib::ratiof(LANDMaxZ, 99, waterPercent) -0.000001;
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
	drawWater(w, m);

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
