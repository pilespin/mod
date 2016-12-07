
#pragma once

#include <project.hpp>
#include "Map.hpp"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_opengl.h>

class Sdl {

public:
	Sdl();
	~Sdl();
	// Sdl(Sdl const &src);
	// Sdl &operator=(Sdl const &rhs);

	int		getValue() const;

	void	setWindowSize(int y, int x);
	void	setWindowName(std::string name);

	void	init(Map m);
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
	
	void	initMatrix();
	void 	rotXUp();
	void 	rotXDown();
	void 	rotYUp();
	void 	rotYDown();
	void 	rotZUp();
	void 	rotZDown();
	void 	translationXDown();
	void 	translationXUp();
	void 	translationYDown();
	void 	translationYUp();
	void 	translationZDown();
	void 	translationZUp();
	void	changeWaterMode1();
	void	changeWaterMode2();
	void	changeWaterMode3();
	void 	zoomIn();
	void 	zoomOut();

	void	initKey();
	void 	moveToEscape();

	SDL_Surface		*getImage(std::string name);
	SDL_Surface		*loadImage(std::string path, std::string newname);

	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			createWindow();
	void			createRenderer();

	void	preparateLand(Map m);
	void	drawFourSide(Map m);
	void	drawWater(Map m, Map l);
	void	drawRain(Map &m, Map l);
	void	drawWave(Map &m, Map l);
	void	drainWater(Map &m, Map l);

	std::map<unsigned char, void (Sdl::*)()> 		keymap;
	std::map<std::string, SDL_Surface *> 	img;

	int 			_val;
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
	std::string		windowName;
	int 			squareSize;
	int 			windowSizeX;
	int 			windowSizeY;
	int 			waterPercent;
	Map				w;
	eDrawMode 		drawMode;

	int		rotX;
	int		rotY;
	int		rotZ;
	float 	tranX;
	float 	tranY;
	float 	tranZ;
	float 	scaleX;
	float 	scaleY;
	float 	scaleZ;

	float 	waterWidth;

	float		mousePosX;
	float		mousePosY;
	bool		mouseMoving;
	bool		mouseMovingTranslation;

	GLuint	listLAND;
	GLuint	listLANDSize;
	float 	LANDMaxZ;

};

std::ostream &operator<<(std::ostream &o, Sdl &c);
