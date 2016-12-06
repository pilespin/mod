
#include <project.hpp>
#include "Map.hpp"
#include "Sdl.hpp"

Sdl::Sdl() {
	_val = 0;
	windowSizeX = 800;
	windowSizeY = 800;
	windowName = "No name";
	// last_time = mylib::utime();
	window = NULL;
	renderer = NULL;
	waterPercent = 5;
	waterWidth = 1;
	drawMode = eDrawMode::Wave;
	initMatrix();
	LANDMaxZ = 0;
	mousePosX = 0;
	mousePosY = 0;
	mouseMoving = false;
	// w = NULL;
}

Sdl::~Sdl() {
	for (auto it = img.begin(); it != img.end(); it++) {
		if (it->second)
			SDL_FreeSurface(it->second);
	}
	quit();
}

// Sdl::Sdl(Sdl const &src)	{	
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
int				Sdl::getValue() const			{	return (_val);		}
void			Sdl::setWindowName(std::string name) {
	if (name.length() > 0)
	{
		windowName.erase();
		windowName = name;
	}
	else
		throw Error("Error: Bad name");
}

SDL_Surface		*Sdl::getImage(std::string name) {	
	if (img[name])
		return (img[name]);
	else
	{
		std::cerr << "Image not found: " << name << std::endl;
		throw Error("Error: Image not found");
	}
}

void			Sdl::setWindowSize(int x, int y) {
	if (x > 0 && x < 16000 && y > 0 && y < 16000)
	{
		windowSizeX = x;
		windowSizeY = y;
	}
	else
		throw Error("Error: Window size is too small or too big");
}
///////////////////////////////////////////////////////////////////////////////
void	Sdl::initMatrix() {
	rotX 	= 45;
	rotY 	= 180;
	rotZ 	= 45;
	tranX 	= -0.5;
	tranY 	= -0.5;
	tranZ 	= 0;
}

void	Sdl::init(Map m) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	setWindowSize(windowSizeX, windowSizeY);
	setWindowName("Mod");
	createWindow();
	createRenderer();
	initKey();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND); 
	glClearColor(0.0,0.0,0.0,0.0);
    // loadImage("img/squareyellow.png", "squareyellow");
	preparateLand(m);
	w = Map(std::vector<Vector> {0}, m.getMapSizeX(), m.getMapSizeY(), 1, 0.0);
	LANDMaxZ = m.getZMax() / m.getMapSizeX();
	// w.printMap();
}

void	Sdl::quit() {

	glDeleteLists(listLAND, listLANDSize);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void	Sdl::drawRectangle(int posX, int posY, int sizeX, int sizeY) {

	SDL_Rect r;

	r.x = posX;
	r.y = posY;
	r.w = sizeX;
	r.h = sizeY;
	SDL_RenderDrawRect(renderer, &r);
	SDL_RenderFillRect(renderer, &r);
}

void	Sdl::createWindow() {

	window = SDL_CreateWindow(windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSizeX, 
		windowSizeY, 
		SDL_WINDOW_OPENGL);

	if(!window)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating window");
	}
}

void	Sdl::createRenderer() {

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating renderer");
	}
}

SDL_Surface	*Sdl::loadImage(std::string path, std::string newname) {

	SDL_Surface     *bmp = IMG_Load(path.c_str());
	if (!bmp){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when atempt to load image: \"" + path + "\"");
	}

	if (newname.length() > 0 && !img[newname])
		img[newname] = bmp;
	else
		throw Error("Error: An image with the same name already exist");

	return (bmp);
}

void	Sdl::DrawImageInRenderer(SDL_Surface *img, int x, int y) {

	SDL_Texture	*texture;
	SDL_Rect	dest;

	texture = SDL_CreateTextureFromSurface(renderer, img);
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w = squareSize;
	dest.h = squareSize;
	SDL_RenderCopy(renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}
