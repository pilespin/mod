
#pragma once

#include <project.hpp>
#include "Map.hpp"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class Sdl {

public:
	Sdl();
	~Sdl();
	// Sdl(Sdl const &src);
	// Sdl &operator=(Sdl const &rhs);

	int		getValue() const;

	void	setWindowSize(int y, int x);
	void	setWindowName(std::string name);

	void	init();
	void 	getKey();
	void	quit();
	void	draw(Map m);
	void	drawRectangle(int posX, int posY, int sizeX, int sizeY);
	void 	waterFixedDown();
	void 	waterFixedUp();


	class Error : public std::exception {
	public:
		Error(std::string str) 						{	this->line += str;				}
		virtual const char *what() const throw() 	{	return (this->line.c_str());	}
	private:
		std::string line;
	};

private:

	void	initKey();
	void 	moveToEscape();

	SDL_Window		*getWindow() const;
	SDL_Renderer 	*getRenderer() const;
	SDL_Surface		*getImage(std::string name);
	SDL_Surface		*loadImage(std::string path, std::string newname);

	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			createWindow();
	void			createRenderer();

	Vector			transform3dTo2d(Vector v);
	void 			isometricViewAngleUp();
	void 			isometricViewAngleDown();

	std::map<char, void (Sdl::*)()> 		keymap;
	std::map< std::string, SDL_Surface * > 	img;

	int 			_val;
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
	std::string		windowName;
	int 			squareSize;
	int 			windowSizeX;
	int 			windowSizeY;
	double			last_time;
	int 			waterPercent;

	int IsometricViewAngle;
};

std::ostream &operator<<(std::ostream &o, Sdl &c);
