
#include <project.hpp>
#include "Sdl.hpp"

///////////////////////////////   KEY   ///////////////////////////////////////
void 	Sdl::moveToEscape() 		{	throw Error("Goodbye");	}
///////////////////////////////   KEY   ///////////////////////////////////////

Sdl::Sdl() {
	this->_val = 0;
	this->windowSizeX = 800;
	this->windowSizeY = 800;
	this->windowName = "Hello";
	this->last_time = mylib::utime();
	this->window = NULL;
	this->renderer = NULL;
}

Sdl::~Sdl() {
	for (auto it = this->img.begin(); it != this->img.end(); it++) {
		if (it->second)
			SDL_FreeSurface(it->second);
	}
	this->quit();
}

Sdl::Sdl(Sdl const &src)	{
	(void)src;		
}

Sdl	&Sdl::operator=(Sdl const &rhs) {

	if (this != &rhs)
	{
	}
	return (*this);
}

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

	this->keymap[SDLK_ESCAPE]			= &Sdl::moveToEscape;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	this->setWindowSize(this->windowSizeX, this->windowSizeY);
	this->setWindowName("mod");
	this->createWindow();
	this->createRenderer();
    // SDL_SetRenderDrawColor(this->getRenderer(), 175, 95, 255, 255); //BackGround

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

void	Sdl::draw(std::vector<std::vector<int>> map, Map m) {
	(void)map;
	(void)m;
	int sizeX = this->windowSizeX / m.getMapSizeX();
	int sizeY = this->windowSizeY / m.getMapSizeY();

    SDL_SetRenderDrawColor(this->getRenderer(), 175, 95, 255, 255); //BackGround
    SDL_RenderClear(this->getRenderer());
    for (int y = 0; y != m.getMapSizeY(); y++)
    {
    	for (int x = 0; x != m.getMapSizeX(); x++)
    	{
    		SDL_SetRenderDrawColor( this->getRenderer(), m.getMap()[x][y] * 20, 0, 0, 0);
    		drawRectangle(sizeX * x, sizeY * y, sizeX, sizeY);
    	}
    }

    // SDL_SetRenderDrawColor( this->getRenderer(), 0, 200, 200, 0);
    // drawRectangle(50, 50, 50, 50);

    // SDL_SetRenderDrawColor( this->getRenderer(), 200, 200, 0, 255);
    // drawRectangle(200, 200, 50, 50);

    SDL_RenderPresent(this->getRenderer());
}

void	Sdl::drawRectangle(int posX, int posY, int sizeX, int sizeY) {

	SDL_Rect r;
	r.x = posX;
	r.y = posY;
	r.w = sizeX;
	r.h = sizeY;
	SDL_RenderDrawRect(this->getRenderer(), &r);
	SDL_RenderFillRect( this->getRenderer(), &r );
}

void	Sdl::createWindow() {

	this->window = SDL_CreateWindow(this->windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowSizeX, 
		this->windowSizeY, 
		SDL_WINDOW_SHOWN);

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
