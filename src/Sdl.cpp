
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
///////////////////////////////   KEY   ///////////////////////////////////////

void	Sdl::initKey() {

	keymap[SDLK_ESCAPE]			= &Sdl::moveToEscape;
	keymap[SDLK_w]				= &Sdl::waterFixedUp;
	keymap[SDLK_x]				= &Sdl::waterFixedDown;
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
	// keymap[SDL_SCANCODE_KP_4]	= &Sdl::translationZUp;
	// keymap[SDL_SCANCODE_KP_1]	= &Sdl::translationZDown;
	keymap[SDLK_SPACE]			= &Sdl::initMatrix;
}

Sdl::Sdl() {
	_val = 0;
	windowSizeX = 800;
	windowSizeY = 800;
	windowName = "No name";
	// last_time = mylib::utime();
	window = NULL;
	renderer = NULL;
	waterPercent = 5;
	initMatrix();
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
	rotX 	= 135;
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

    // loadImage("img/squareyellow.png", "squareyellow");
	preparateMap(m);
}

void	Sdl::quit() {

	glDeleteLists(listMAP, listMAPSize);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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

void	preparateMapVertex(Map m, float x, float y, int maxZ) {

	glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y)), 0);
	glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y)/m.getMapSizeX() );

	glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y)), 0);
	glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y)/m.getMapSizeX() );

	glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y+1)), 0);
	glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1)/m.getMapSizeX() );

	glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y+1)), 0);
	glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1)/m.getMapSizeX() );

}

void	Sdl::preparateMap(Map m) {

	float x;
	float y;
	int maxZ = m.getZMax();

	listMAP = glGenLists(1);
	listMAPSize = 0;
	glNewList(listMAP, GL_COMPILE);
	glBegin(GL_QUADS);
	for (y = m.getMapSizeY(); y != 0; y--)
	{
		for (x = m.getMapSizeX(); x != 0; x--)
		{
			// preparateMapVertex(m, x, y, maxZ);	
			// float zColor	= mylib::ratiof(1, maxZ, m.getMap(x,y));
			// std::cout << "color: " << mylib::ratiof(100, maxZ, m.getMap(x,y)) << std::endl;
			// if (waterPercent >= mylib::ratiof(100, maxZ, m.getMap(x,y))+1)
			// {
			// 	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			// 	glColor3f(0.1,0.8,0.6);
			// }	// glColor3f(0,0,0);
			// else
			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y)), 0);
			glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y)), 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y+1)), 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y+1)), 0);
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1)/m.getMapSizeX() );

			// glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeX(),    	m.getMap(x,y) 		/m.getMapSizeX() );
			// glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeX(),      m.getMap(x+1,y+1) 	/m.getMapSizeX() );
			// glVertex3f( (x)/m.getMapSizeX(),  	(y+1)/m.getMapSizeX(), 		m.getMap(x,y+1) 	/m.getMapSizeX() );
			listMAPSize++;
		}
	}
	glEnd();
	glEndList();

	listMAPReverse = glGenLists(1);
	glNewList(listMAPReverse, GL_COMPILE);
	glBegin(GL_QUADS);
	for (y = 0; y != m.getMapSizeY(); y++)
	{
		for (x = 0; x != m.getMapSizeX(); x++)
		{
			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y)), 0);
			glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeY(),    	m.getMap(x,y)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y)), 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y)/m.getMapSizeY(),      	m.getMap(x+1,y)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x+1,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x+1,y+1)), 0);
			glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeY(), 		m.getMap(x+1,y+1)/m.getMapSizeX() );

			glColor3f(0.5+mylib::ratiof(0.5, maxZ, m.getMap(x,y+1)), 0.3+mylib::ratiof(0.3, maxZ, m.getMap(x,y+1)), 0);
			glVertex3f( (x)/m.getMapSizeX(),	(y+1)/m.getMapSizeY(), 	  	m.getMap(x,y+1)/m.getMapSizeX() );

			// glVertex3f( (x)/m.getMapSizeX(),    (y)/m.getMapSizeX(),    	m.getMap(x,y) 		/m.getMapSizeX() );
			// glVertex3f( (x+1)/m.getMapSizeX(),  (y+1)/m.getMapSizeX(),      m.getMap(x+1,y+1) 	/m.getMapSizeX() );
			// glVertex3f( (x)/m.getMapSizeX(),  	(y+1)/m.getMapSizeX(), 		m.getMap(x,y+1) 	/m.getMapSizeX() );
		}
	}
	glEnd();
	glEndList();
}

void	Sdl::draw(Map m) {
	(void)m;

	glClearColor( 0.25f, 0.5f, 0.9f, 0.0f );
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

	// glMatrixMode(GL_PROJECTION);
	// glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tranX, tranY, tranZ);
	glTranslatef(0.5, 0.5, 0);
	glRotatef(rotX, 1.0, 0.0, 0.0);
	glRotatef(rotY, 0.0, 1.0, 0.0);
	glRotatef(rotZ, 0.0, 0.0, 1.0);
	glTranslatef(-0.5, -0.5, 0);

	if (rotZ > 270 || rotZ <= 90)
		glCallList(listMAPReverse);
	else
		glCallList(listMAP);
	glPopMatrix();

	SDL_RenderPresent(renderer);
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
