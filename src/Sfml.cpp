
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

void 	Sfml::Calcul(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat X;
	GLfloat Y;

	X = std::sqrt(2.0)/2.0 * (x - y);
	Y = (std::sqrt(2.0/3.0)* z) - ((1.0 /std::sqrt(6.0)) * (x + y));

	glVertex2f((X)/500.0 , (Y)  /500 );

}

void	Sfml::draw(Map map) {

	GLuint       list_;
	static int  t = time(NULL); 
	static int a = 0;
	static int b = 0;
  	// GLfloat g_color_buffer_data[500];

	GLfloat  x;
	GLfloat  y;
	int n = 0;
	// this->window.clear(sf::Color(175, 95, 255, 255));
	// this->window.clear(sf::Color(0, 0, 0, 255));
        	GLfloat tr_s = 5;
    
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
          // glVertex3f((x/*+500*/)/500.0  - 0.5, (y/*+500.0*/)/500.0-0.5, static_cast<GLfloat>(map.access(x, y))/500.0 - 0.5);
          // glVertex3f((x/*+500.0*/+tr_s)/500.0 - 0.5, (y/*+tr_s00.0*/)/500.0-0.5, static_cast<GLfloat>(map.access(x+1, y))/500.0 - 0.5);
          // glVertex3f((x/*+tr_s00.0*/+tr_s)/500.0 - 0.5, (y/*+tr_s00.0*/+tr_s)/500.0-0.5, static_cast<GLfloat>(map.access(x+1, y+1))/500.0 - 0.5);
  			
  		// glColor3f (1.0, 0.0, 0.0);
          this->Calcul(x,y, static_cast<GLfloat>(map.access(x, y)));
          this->Calcul(x+tr_s,y, static_cast<GLfloat>(map.access(x, y)));
          this->Calcul(x+tr_s,y+tr_s, static_cast<GLfloat>(map.access(x, y)));
          

          this->Calcul(x,y, static_cast<GLfloat>(map.access(x, y)));
          this->Calcul(x,y+tr_s, static_cast<GLfloat>(map.access(x, y)));
          this->Calcul(x+tr_s,y+tr_s, static_cast<GLfloat>(map.access(x, y)));

          // glVertex3f((x/*+tr_s00.0*/)/500.0 - 0.5, (y/*+tr_s00.0*/)/500.0-0.5, static_cast<GLfloat>(map.access(x, y))/500.0 - 0.5);
          // glVertex3f((x/*+tr_s00.0*/+tr_s)/500.0 - 0.5, (y/*+tr_s00.0*/+tr_s)/500.0-0.5, static_cast<GLfloat>(map.access(x+1, y+1))/500.0 - 0.5);
          // glVertex3f((x/*+tr_s00.0*/)/500.0 - 0.5, (y/*+tr_s00.0*/+tr_s)/500.0 - 0.5, static_cast<GLfloat>(map.access(x, y+1))/500.0 - 0.5);
  			n +=2;
          // g_color_buffer_data[x+y]
                                    
                                    
          y+=tr_s;
        }
        x+=tr_s;
      }
 
    glEnd();
  glEndList();
  glColor3f (0.0, 0.0, 0.0);
  // GLfloat g_color_buffer_data = 0.583f;
   glClear          ( GL_COLOR_BUFFER_BIT ); // Réinitialisation z-buffer

// glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
//    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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
	if (std::time(NULL) > t)
	{
		t = time(NULL);
		b = a;
		a = 0;
	}
	std::cout<<b<<std::endl;
a++;
            // std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            // exit(0);
	// std::cout<<"a"<<std::endl;
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
