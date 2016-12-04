
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
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x,y) );
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x,y) );
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y) );
		}
	}
	glEnd();
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
		std::cout << "Rain Selected" << std::endl;
	}
	drawWater(w);

	glPopMatrix();

	SDL_RenderPresent(renderer);
}
