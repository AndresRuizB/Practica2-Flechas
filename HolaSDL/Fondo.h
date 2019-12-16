#pragma once
#include "ArrowsGameObject.h"

class App;

class Fondo:public ArrowsGameObject
{
public:
	Fondo(App* a);
	~Fondo();
	virtual void render();
	virtual void update() {};
	virtual SDL_Rect getDestRect() { return SDL_Rect(); };
	virtual SDL_Rect getCollisionRect() { return SDL_Rect(); };
	virtual void loadFromFile(ifstream* input) {};
	virtual void saveToFile(ofstream* output) {};
	virtual void setItList(list<GameObject*>::iterator it) {};
private:
	App* app;
};