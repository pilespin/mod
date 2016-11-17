/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 17:09:38 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class Sdl {

public:
	Sdl();
	~Sdl();
	Sdl(Sdl const &src);
	Sdl &operator=(Sdl const &rhs);

	int		getValue() const;

	void	setWindowSize(int y, int x);
	void	setWindowName(std::string name);

	void	init();
	void 	getKey();
	void	quit();
	void	draw();

	class Error : public std::exception {
	public:
		Error(std::string str) 						{	this->line += str;				}
		virtual const char *what() const throw() 	{	return (this->line.c_str());	}
	private:
		std::string line;
	};

private:

	void 	moveToEscape();

	SDL_Window		*getWindow() const;
	SDL_Renderer 	*getRenderer() const;
	SDL_Surface		*getImage(std::string name);
	SDL_Surface		*loadImage(std::string path, std::string newname);

	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			createWindow();
	void			createRenderer();

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
};

std::ostream &operator<<(std::ostream &o, Sdl &c);
