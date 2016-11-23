/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 19:32:44 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Sdl.hpp"

static double  ft_utime()
{
	int             sec;
	double          micro;
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	micro /= 1000000;
	micro += sec;
	return (micro);
}

///////////////////////////////   KEY   ///////////////////////////////////////
void 	Sdl::moveToEscape() 		{	throw Error("Goodbye");	}

void 	Sdl::isometricViewAngleUp() 		{	
	if (this->IsometricViewAngle < 360)
		this->IsometricViewAngle++;
}
void 	Sdl::isometricViewAngleDown() 		{	
	if (this->IsometricViewAngle > 0)
		this->IsometricViewAngle--;
}
///////////////////////////////   KEY   ///////////////////////////////////////

Sdl::Sdl() {
	this->_val = 0;
	this->windowSizeX = SCREEN_SIZE;
	this->windowSizeY = SCREEN_SIZE;
	this->windowName = "Hello";
	this->last_time = ft_utime();
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
	this->keymap[SDL_SCANCODE_RIGHT]	= &Sdl::isometricViewAngleUp;
	this->keymap[SDL_SCANCODE_LEFT]		= &Sdl::isometricViewAngleDown;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	// SDL_SetVideoMode(this->windowSizeX, this->windowSizeY, 32, SDL_OPENGL);
	this->setWindowSize(this->windowSizeX, this->windowSizeY);
	this->setWindowName("mod");
	this->createWindow();
	this->createRenderer();
	this->IsometricViewAngle = 240;
    SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 0); //BackGround
    
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

void 	Sdl::draw_pixel(double x, double y, double h)
{
	// double IsometricViewAngle =130;

	double XDelta = std::cos(this->IsometricViewAngle * M_PI / 180.0);
	double YDelta = std::sin(this->IsometricViewAngle * M_PI / 180.0);
	double ZDelta = 0.8;

	// OK, that it, now I'm going to Project 3D points into 2D point:

	double X = (-x * XDelta) + (-y * YDelta);
	double Y = (-x * XDelta) + (-h * ZDelta);

	// Dim ProjectedPoint As New Point(X,Y)
	// return (Vector(X, Y, 0));

	SDL_Rect r;
	double i;
	(void)h;
	r.x = X + (SCREEN_SIZE * 0.2) -1;
	r.y = Y + (SCREEN_SIZE * 0.5) -1;
	r.w = 3;
	r.h = 3 ;
	i = 0 ;
	SDL_RenderDrawRect(this->renderer, &r);
	SDL_RenderFillRect(this->renderer, &r);

}

int			ratio(int maxVal1, int maxVal2, double yourVal) {

	return (maxVal1 * static_cast<int>(yourVal) / maxVal2);
}

void	Sdl::draw(Map m) {

	SDL_GLContext opengl3_context;
	(void)opengl3_context;

	int x;
	int y;
	SDL_RenderClear(this->getRenderer());
	// (void)m;
	x = 0;
    // SDL_SetRenderDrawColor(this->getRenderer(), 0, 255-100, 255-100, 255-100);
	// draw_pixel(5, 5);
    // SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 0);


	while (x < MAX_SIZE)
	{
		y = 0;
		while (y < MAX_SIZE)
		{
			// if (y == 250)
			// 	printf("%lf\n", m.access(x,y));
			// if (m.access(x, y) < 100)
   //  			SDL_SetRenderDrawColor(this->getRenderer(), 0, 255-100, 255-100,  0);
   //  		else if (m.access(x, y) < 200)
   //  			SDL_SetRenderDrawColor(this->getRenderer(), 0, 255-60, 255-60, 0);
   //  		else if (m.access(x, y) < 300)
   //  			SDL_SetRenderDrawColor(this->getRenderer(), 0, 255-40, 255-40, 0);
   //  		else if (m.access(x, y) < 400)
   //  			SDL_SetRenderDrawColor(this->getRenderer(), 0, 255-20, 255-20, 0);
   //  		else
			SDL_SetRenderDrawColor(this->getRenderer(), ratio(215, MAX_SIZE, m.access(x, y))+50, 50+ratio(90, MAX_SIZE, m.access(x, y)), 0 , 250);
			draw_pixel(static_cast<double>(x), static_cast<double>(y), m.access(x, y));
    		// return ;

			y++;
		}
		x++;
	}

	SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 0);
	SDL_RenderPresent(this->getRenderer());

	 // while(1);
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

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_WINDOW_OPENGL | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
