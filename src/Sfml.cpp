
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

	// this->window = window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	// window.setVerticalSyncEnabled(true);
    this->window.create(sf::VideoMode(800, 600), "OpenGL");

	// sf::Window window(sf::VideoMode(800, 600), "OpenGL");

// it works out of the box
	// glEnable(GL_TEXTURE_2D);

	// sf::Window window(sf::VideoMode(800, 600), "OpenGL");
}

void	Sfml::draw() {


	// this->window.clear(sf::Color(175, 95, 255, 255));

        // effacement les tampons de couleur/profondeur
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // dessin...

        // termine la trame courante (en interne, échange les deux tampons de rendu)
	window.display();


    // libération des ressources...

}

void	Sfml::getKey() {

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
                // on stoppe le programme
			// running = false;
		}
		else if (event.type == sf::Event::Resized)
		{
                // on ajuste le viewport lorsque la fenêtre est redimensionnée
			// glViewport(0, 0, event.size.width, event.size.height);
		}
	}
	
}

void	Sfml::empty() {

}
