
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

}

void	Sfml::draw() {


	// this->window.clear(sf::Color(175, 95, 255, 255));
	this->window.clear(sf::Color(0, 0, 0, 255));
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
