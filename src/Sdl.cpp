
#include <project.hpp>
#include "Sdl.hpp"

///////////////////////////////   KEY   ///////////////////////////////////////
void 	Sdl::moveToEscape() 		{	throw Error("Goodbye");	}
void 	Sdl::waterFixedUp() 		{	
	if (this->waterPercent < 100)
		this->waterPercent++;	
	std::cout << "Water UP " << waterPercent << " %" << std::endl;
}
void 	Sdl::waterFixedDown() 		{	
	if (this->waterPercent > 0)
		this->waterPercent--;
	std::cout << "Water DOWN " << waterPercent << " %" << std::endl;
}
void 	Sdl::isometricViewAngleUp() 		{	

	glPushMatrix();
	// glTranslatef(-0.5, -0.5, 0.0);
	glTranslatef(-0.7, 0.0, 0.0);
}
void 	Sdl::isometricViewAngleDown() 		{	
	if (this->IsometricViewAngle > 0)
		this->IsometricViewAngle--;
}
///////////////////////////////   KEY   ///////////////////////////////////////

void	Sdl::initKey() {

	this->keymap[SDLK_ESCAPE]			= &Sdl::moveToEscape;
	this->keymap[SDL_SCANCODE_UP]		= &Sdl::waterFixedUp;
	this->keymap[SDL_SCANCODE_DOWN]		= &Sdl::waterFixedDown;
	this->keymap[SDL_SCANCODE_RIGHT]	= &Sdl::isometricViewAngleUp;
	this->keymap[SDL_SCANCODE_LEFT]		= &Sdl::isometricViewAngleDown;
}

Sdl::Sdl() {
	this->_val = 0;
	this->windowSizeX = 800;
	this->windowSizeY = 800;
	this->windowName = "Hello";
	this->last_time = mylib::utime();
	this->window = NULL;
	this->renderer = NULL;
	this->waterPercent = 5;
	this->IsometricViewAngle = 135;
}

Sdl::~Sdl() {
	for (auto it = this->img.begin(); it != this->img.end(); it++) {
		if (it->second)
			SDL_FreeSurface(it->second);
	}
	this->quit();
}

// Sdl::Sdl(Sdl const &src)	{
// 	this->keymap = src.keymap;
// 	this->img = src.img;

// 	this->_val = src._val;
// 	this->window = src.window;
// 	this->renderer = src.renderer;
// 	this->windowName = src.windowName;
// 	this->squareSize = src.squareSize;
// 	this->windowSizeX = src.windowSizeX;
// 	this->windowSizeY = src.windowSizeY;
// 	this->last_time = src.last_time;		
// }

// Sdl	&Sdl::operator=(Sdl const &rhs) {

// 	if (this != &rhs)
// 	{
// 	}
// 	return (*this);
// }

std::ostream &operator<<(std::ostream &o, Sdl &c) {
	o << "Sdl: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int				Sdl::getValue() const			{	return (this->_val);		}
SDL_Window		*Sdl::getWindow() const			{	return (this->window);		}
SDL_Renderer	*Sdl::getRenderer() const		{	return (this->renderer);	}

void			Sdl::setWindowName(std::string name) {
	if (name.length() > 0)
	{
		this->windowName.erase();
		this->windowName = name;
	}
	else
		throw Error("Error: Bad name");
}

SDL_Surface		*Sdl::getImage(std::string name) {	
	if (this->img[name])
		return (this->img[name]);
	else
	{
		std::cerr << "Image not found: " << name << std::endl;
		throw Error("Error: Image not found");
	}
}

void			Sdl::setWindowSize(int x, int y) {
	if (x > 0 && x < 16000 && y > 0 && y < 16000)
	{
		this->windowSizeX = x;
		this->windowSizeY = y;
	}
	else
		throw Error("Error: Window size is too small or too big");
}
///////////////////////////////////////////////////////////////////////////////

void	Sdl::init() {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	this->setWindowSize(this->windowSizeX, this->windowSizeY);
	this->setWindowName("mod");
	this->createWindow();
	this->createRenderer();
	this->initKey();
    // SDL_SetRenderDrawColor(this->getRenderer(), 20, 20, 255, 255); //BackGround    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    	// Set our OpenGL version.
	// // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// // Turn on double buffering with a 24bit Z buffer.
	// // You may need to change this to 16 or 32 for your system
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// // This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	glEnable(GL_TEXTURE_2D);


	glPushMatrix();
	// glTranslatef(-0.5, -0.5, 0.0);
	glTranslatef(-0.7, 0.0, 0.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
    // glRotatef(-10.0, 1.0, 1.0, 1.0);

    // this->loadImage("img/squareyellow.png", "squareyellow");
}

void	Sdl::quit() {
	SDL_DestroyRenderer(this->getRenderer());
	SDL_DestroyWindow(this->getWindow());
	SDL_Quit();
}

void 	Sdl::getKey(void) {

	SDL_Event   e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			throw Error("Goodbye");
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (keymap[e.key.keysym.sym])
				(this->*(keymap[e.key.keysym.sym]))();
		}
	}
}

void	Sdl::draw(Map m) {

	// GLuint	list_ = glGenLists(1);
	// glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
	// glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	// glNewList(list_, GL_COMPILE);
	// glBegin(GL_TRIANGLES);
	glBegin(GL_QUADS);
	// glEnable(GL_BLEND);
	int maxZ = m.getZMax();
	for (float y = 0; y != m.getMapSizeY(); y++)
	{
		for (float x = 0; x != m.getMapSizeX(); x++)
		{
			// float zColor	= mylib::ratiof(1, maxZ, m.getMap(x,y));
			// std::cout << "color: " << mylib::ratiof(100, maxZ, m.getMap(x,y)) << std::endl;
			// if (this->waterPercent > mylib::ratiof(100, maxZ, m.getMap(x,y)))
			// {
			// 	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			// 	glColor3f(0.1,0.8,0.6);
			// }	// glColor3f(0,0,0);
			// else
			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y)), 0);
			glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y)/m.getMapSizeX() );
			// glColor3f(mylib::ratiof(0.5, maxZ, m.getMap(x+1,y)), 0, 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y)/m.getMapSizeX() );
			// glColor3f(mylib::ratiof(0.5, maxZ, m.getMap(x+1,y+1)), 0, 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1)/m.getMapSizeX() );
			// glColor3f(mylib::ratiof(0.5, maxZ, m.getMap(x,y+1)), 0, 0);
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1)/m.getMapSizeX() );

			// glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeX(),    	m.getMap(x,y) 		/m.getMapSizeX() );
			// glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeX(),      m.getMap(x+1,y+1) 	/m.getMapSizeX() );
			// glVertex3f( (x)/m.getMapSizeX(),  	(y+1)/m.getMapSizeX(), 		m.getMap(x,y+1) 	/m.getMapSizeX() );

		}
	}
	glEnd();
	// glPopMatrix();

	// glEndList();
	// glCallList(list_);
	// glDeleteLists(list_, m.getMapSizeX() * m.getMapSizeY());

	std::cout << "Passed" << std::endl;
	SDL_RenderPresent(this->getRenderer());
}

// Vector	Sdl::transform3dTo2d(Vector v) {

//     //I've found a way to project 3D into Isometric 2D.

// 	// I Supposed a angle for Isometric View and of course, a 3D point to project like

// 	// Dim IsometricViewAngle As Integer = 30
// 	// int IsometricViewAngle = 90;
// 	// Vector v = Vector(dx,dy1,dz);

// 	// which dx, dy and dz are your custom values. 
// 	// then I had to calculate a Delta Value for X and Y Increments and Decrements like

// 	double XDelta = std::cos(IsometricViewAngle * M_PI / 360);
// 	double YDelta = std::sin(IsometricViewAngle * M_PI / 360);
// 	double ZDelta = 0.8;

// 	// OK, that it, now I'm going to Project 3D points into 2D point:

// 	double X = (-v.x * XDelta) + (-v.y * YDelta);
// 	double Y = (-v.x * XDelta) + (-v.z * ZDelta);

// 	// Dim ProjectedPoint As New Point(X,Y)
// 	return (Vector(X, Y, 0));

// }

// Vector	Sdl::transform3dTo2d(Vector v) {

// 	double X = v.x / (v.z + 0.01);
// 	double Y = v.y / (v.z + 0.01);

// 	return (Vector(X, Y, 0));
// }

void	Sdl::drawRectangle(int posX, int posY, int sizeX, int sizeY) {

	SDL_Rect r;

	r.x = posX;
	r.y = posY;
	r.w = sizeX;
	r.h = sizeY;
	SDL_RenderDrawRect(this->getRenderer(), &r);
	SDL_RenderFillRect(this->getRenderer(), &r);
}

void	Sdl::createWindow() {

	this->window = SDL_CreateWindow(this->windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowSizeX, 
		this->windowSizeY, 
		SDL_WINDOW_OPENGL);

	if(!this->window)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating window");
	}
}

void	Sdl::createRenderer() {

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!this->renderer)
	{
		SDL_DestroyWindow(this->window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating renderer");
	}
}

SDL_Surface	*Sdl::loadImage(std::string path, std::string newname) {

	SDL_Surface     *bmp = IMG_Load(path.c_str());
	if (!bmp){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when atempt to load image: \"" + path + "\"");
	}

	if (newname.length() > 0 && !this->img[newname])
		this->img[newname] = bmp;
	else
		throw Error("Error: An image with the same name already exist");

	return (bmp);
}

void	Sdl::DrawImageInRenderer(SDL_Surface *img, int x, int y) {

	SDL_Texture	*texture;
	SDL_Rect	dest;

	texture = SDL_CreateTextureFromSurface(this->renderer, img);
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w = this->squareSize;
	dest.h = this->squareSize;
	SDL_RenderCopy(this->renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}
