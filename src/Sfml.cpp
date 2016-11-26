
#include "Sfml.hpp"

Sfml::Sfml() 						{	this->_val = 0;	}

Sfml::~Sfml()						{}

Sfml::Sfml(Sfml const &src)	{	
	this->_val = src._val;
}

Sfml	&Sfml::operator=(Sfml const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Sfml &c) {
	o << "I'm Sfml class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Sfml::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////
void	Sfml::init() {

    this->window.create(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "SFML");
	glEnable(GL_TEXTURE_2D);
}

float			ratio(float maxVal1, float maxVal2, double yourVal) {

	return ((maxVal1 * static_cast<float>(yourVal) / maxVal2)/255.0);
}

void	Sfml::draw(Map map) {

	GLuint       list_;
  	// GLfloat g_color_buffer_data[500];

	GLfloat  x;
	GLfloat  y;
	int n = 0;
	// this->window.clear(sf::Color(175, 95, 255, 255));
	// this->window.clear(sf::Color(0, 0, 0, 255));
    
    list_ = glGenLists( 1 );
  
  // On demande à OpenGL de compiler ce qui va suivre dans
  // une display list identifiée par list_, que l'on vient de
  // générer.
  glNewList( list_, GL_COMPILE );
    // Nous informons OpenGL que ce qui va suivre est une
    // énumération de triangles.
    glBegin( GL_TRIANGLES );
      //  Pour chaque ligne, avec un pas dépendant de la précision souhaitée
      x = 0;
      while (x < MAX_SIZE - 1.0)
      {
        // Pour chaque colonne, avec un pas dépendant de la précision souhaitée
        y = 0;
        while (y < MAX_SIZE  - 1.0)
        {
  			glColor3f (ratio(255, MAX_SIZE, map.access(x, y))+50.0/255.00, 50.0/255.0+ratio(90, MAX_SIZE, map.access(x, y)), 0 );

          // Définition des coordonnées des points
          glVertex3f((x/*+500*/)/500.0  - 0.25, (y/*+500.0*/)/500.0-0.5, static_cast<GLfloat>(map.access(x, y))/500.0 - 0.5);
          glVertex3f((x/*+500.0*/+1)/500.0 - 0.5, (y/*+500.0*/)/500.0-0.5, static_cast<GLfloat>(map.access(x+1, y))/500.0 - 0.5);
          glVertex3f((x/*+500.0*/+1)/500.0 - 0.5, (y/*+500.0*/+1)/500.0-0.5, static_cast<GLfloat>(map.access(x+1, y+1))/500.0 - 0.5);
  			
  		// glColor3f (1.0, 0.0, 0.0);
          

          glVertex3f((x/*+500.0*/)/500.0 - 0.5, (y/*+500.0*/)/500.0-0.5, static_cast<GLfloat>(map.access(x, y))/500.0 - 0.5);
          glVertex3f((x/*+500.0*/+1)/500.0 - 0.5, (y/*+500.0*/+1)/500.0-0.5, static_cast<GLfloat>(map.access(x+1, y+1))/500.0 - 0.5);
          glVertex3f((x/*+500.0*/)/500.0 - 0.5, (y/*+500.0*/+1)/500.0 - 0.5, static_cast<GLfloat>(map.access(x, y+1))/500.0 - 0.5);
  			n +=2;
          // g_color_buffer_data[x+y]
                                    
                                    
          y++;
        }
        x++;
      }
 
    glEnd();
  glEndList();
  glColor3f (0.0, 0.0, 0.0);
  // GLfloat g_color_buffer_data = 0.583f;
   glClear          ( GL_COLOR_BUFFER_BIT ); // Réinitialisation z-buffer
   // gluPerspective(45.0f, 0.1f, 0.1f, 100.0f);
  // gluLookAt(	/*GLdouble eyeX*/500.0,
 	// /*GLdouble eyeY*/500.0,
 	// /*GLdouble eyeZ*/500.0,
 	// /*GLdouble centerX*/500.0,
 	// /*GLdouble centerY*/500.0,
 	// /*GLdouble centerZ*/500.0,
 	// /*GLdouble upX*/500.0,
 	// /*GLdouble upY*/500.0,
 	// /*GLdouble upZ*/500.0);
  // // camera_.focus    (                     ); // gluLookAt
  // glScalef         ( 1.f, 0.15, 1.f     ); // Diminution du rapport de hauteur
  // glColor3f (0.0, 1.0, 0.0);
  //glEnable         ( GL_TEXTURE_2D       ); // Activation du texturing
  // texture_main.Bind(                     ); // Sélection de la texture principale
  glCallList       ( list_ );

        // termine la trame courante (en interne, échange les deux tampons de rendu)
window.display();
            // std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            // exit(0);

glDeleteLists(list_, n);


    // libération des ressources...

}

void	Sfml::getKey() {

	sf::Event event;
while (window.pollEvent(event))
{
    switch (event.type)
    {
        case sf::Event::Closed:
            window.close();
            exit(0);

        case sf::Event::KeyPressed:
            // std::cout<<event.key.code<<std::endl;
            if ((event.key.code) == 36)
              {
              	window.close();
            	exit(0);
              }
        default:
            break;
    }
}
	
}

void	Sfml::empty() {

}
