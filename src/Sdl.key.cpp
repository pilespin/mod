
#include <project.hpp>
#include "Sdl.hpp"

///////////////////////////////   KEY   ///////////////////////////////////////

void 	Sdl::moveToEscape() 		{	throw Error("Goodbye");	}
void 	Sdl::waterFixedUp() 		{	
	if (waterPercent < 100)
		waterPercent++;	
	std::cout << "Water UP " << waterPercent << " %" << std::endl;
}
void 	Sdl::waterFixedDown() 		{	
	if (waterPercent > 0)
		waterPercent--;
	std::cout << "Water DOWN " << waterPercent << " %" << std::endl;
}
void 	Sdl::rotXDown() {	
	--rotX %= 360;
	std::cout << "Rotation X " << rotX << "°" << std::endl;
}
void 	Sdl::rotXUp() {	
	++rotX %= 360;
	std::cout << "Rotation X " << rotX << "°" << std::endl;
}
void 	Sdl::rotYDown() {	
	--rotY %= 360;
	std::cout << "Rotation Y " << rotY << "°" << std::endl;
}
void 	Sdl::rotYUp() {	
	++rotY %= 360;
	std::cout << "Rotation Y " << rotY << "°" << std::endl;
}
void 	Sdl::rotZDown() {	
	--rotZ %= 360;
	if (rotZ < 0) rotZ = 359;
	std::cout << "Rotation Z " << rotZ << "°" << std::endl;
}
void 	Sdl::rotZUp() {	
	++rotZ %= 360;
	std::cout << "Rotation Z " << rotZ << "°" << std::endl;
}
void 	Sdl::translationXUp() {	
	tranX += 0.01;
	std::cout << "Translation X " << tranX << std::endl;
}
void 	Sdl::translationXDown() {	
	tranX -= 0.01;
	std::cout << "Translation X " << tranX << std::endl;
}
void 	Sdl::translationYUp() {	
	tranY += 0.01;
	std::cout << "Translation Y " << tranY << std::endl;
}
void 	Sdl::translationYDown() {	
	tranY -= 0.01;
	std::cout << "Translation Y " << tranY << std::endl;
}
void 	Sdl::translationZUp() {	
	tranZ += 0.01;
	std::cout << "Translation Z " << tranZ << std::endl;
}
void 	Sdl::translationZDown() {	
	tranZ -= 0.01;
	std::cout << "Translation Z " << tranZ << std::endl;
}

void	Sdl::changeWaterMode1() {
	drawMode = eDrawMode::ByGround;
}

void	Sdl::changeWaterMode2() {
	drawMode = eDrawMode::Rain;
}
void	Sdl::changeWaterMode3() {
	drawMode = eDrawMode::Wave;
}

void 	Sdl::zoomIn() {	
	scaleX += 0.1;
	scaleY += 0.1;
	std::cout << "Zoom IN" << std::endl;
}

void 	Sdl::zoomOut() {	
	scaleX -= 0.1;
	scaleY -= 0.1;
	if (scaleX < 0.1)
		scaleX = 0.1;
	if (scaleY < 0.1)
		scaleY = 0.1;
	std::cout << "Zoom OUT" << std::endl;
}

void	Sdl::initKey() {

	keymap[SDLK_ESCAPE]			= &Sdl::moveToEscape;
	keymap[SDLK_q]				= &Sdl::waterFixedUp;
	keymap[SDLK_w]				= &Sdl::waterFixedDown;
	keymap[SDL_SCANCODE_DOWN]	= &Sdl::rotXDown;
	keymap[SDL_SCANCODE_UP]		= &Sdl::rotXUp;
	// keymap[SDL_SCANCODE_KP_2]	= &Sdl::rotYDown;
	// keymap[SDL_SCANCODE_KP_5]	= &Sdl::rotYUp;
	keymap[SDL_SCANCODE_LEFT]	= &Sdl::rotZDown;
	keymap[SDL_SCANCODE_RIGHT]	= &Sdl::rotZUp;
	keymap[SDL_SCANCODE_KP_6]	= &Sdl::translationXUp;
	keymap[SDL_SCANCODE_KP_4]	= &Sdl::translationXDown;
	keymap[SDL_SCANCODE_KP_8]	= &Sdl::translationYUp;
	keymap[SDL_SCANCODE_KP_2]	= &Sdl::translationYDown;
	keymap[SDL_SCANCODE_KP_1]	= &Sdl::translationZUp;
	keymap[SDL_SCANCODE_KP_0]	= &Sdl::translationZDown;
	keymap[SDLK_SPACE]			= &Sdl::initMatrix;
	keymap[38]					= &Sdl::changeWaterMode1;
	keymap[SDLK_1]				= &Sdl::changeWaterMode1;
	keymap[233]					= &Sdl::changeWaterMode2;
	keymap[SDLK_2]				= &Sdl::changeWaterMode2;
	keymap[34]					= &Sdl::changeWaterMode3;
	keymap[SDLK_3]				= &Sdl::changeWaterMode3;
	keymap[SDL_SCANCODE_KP_PLUS]	= &Sdl::zoomIn;
	keymap[SDL_SCANCODE_KP_MINUS]	= &Sdl::zoomOut;
	
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
			// std::cout << "pressed: " << e.key.keysym.sym << std::endl;
			if (keymap[e.key.keysym.sym])
				(this->*(keymap[e.key.keysym.sym]))();
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
		{
			std::cout << "Mouse Right DOWN" << std::endl;
			mousePosX = e.motion.x;
			mousePosY = e.motion.y;
			mouseMoving = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Mouse Left DOWN" << std::endl;
			mousePosX = e.motion.x;
			mousePosY = e.motion.y;
			mouseMovingTranslation = true;
		}
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT)
		{
			std::cout << "Mouse Right UP" << std::endl;
			mouseMoving = false;	
		}
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Mouse Left UP" << std::endl;
			mouseMovingTranslation = false;	
		}
		else if (SDL_MOUSEWHEEL)
		{
			if (e.wheel.y == 1)
				zoomIn();
			else if (e.wheel.y == -1)
				zoomOut();
		}
		if (mouseMoving)
		{	
			if (e.motion.x > 0 && e.motion.x <= windowSizeX && 
				e.motion.y > 0 && e.motion.y <= windowSizeY)
			{
				rotZ -= e.motion.x - mousePosX;
				rotX -= e.motion.y - mousePosY;
				mousePosX = e.motion.x;
				mousePosY = e.motion.y;
			}
		}
		if (mouseMovingTranslation)
		{	
			if (e.motion.x > 0 && e.motion.x <= windowSizeX && 
				e.motion.y > 0 && e.motion.y <= windowSizeY)
			{
				tranX += (e.motion.x - mousePosX) / (windowSizeX / 2) / scaleX ;
				tranY -= (e.motion.y - mousePosY) / (windowSizeX / 2) / scaleY ;
				mousePosX = e.motion.x;
				mousePosY = e.motion.y;
			}
		}
	}
}
