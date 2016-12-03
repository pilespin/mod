
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

	void	initKey();
	void 	moveToEscape();

	SDL_Surface		*getImage(std::string name);
	SDL_Surface		*loadImage(std::string path, std::string newname);

	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			createWindow();
	void			createRenderer();

	void	preparateMap(Map m);
	// void	preparateMapVertex(Map m, float x, float y, int maxZ);


	std::map<char, void (Sdl::*)()> 		keymap;
	std::map<std::string, SDL_Surface *> 	img;

	int 			_val;
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
	std::string		windowName;
	int 			squareSize;
	int 			windowSizeX;
	int 			windowSizeY;
	// double			last_time;
	int 			waterPercent;

	int		rotX;
	int		rotY;
	int		rotZ;
	float 	tranX;
	float 	tranY;
	float 	tranZ;

	GLuint	listMAP;
	GLuint	listMAPReverse;
	GLuint	listMAPSize;

};

std::ostream &operator<<(std::ostream &o, Sdl &c);
