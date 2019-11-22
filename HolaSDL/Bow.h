#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include "checkML.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include <list>

class Game;

class Bow:public ArrowsGameObject, public EventHandler
{
private:
	float velFlecha;
	Arrow* flecha;
	bool cargado;
	double angulo;

public:
	Bow(Texture* t, Game* g);
	~Bow();
	//avisa a su textura q se rendere
	virtual void render();
	void handleEvent(SDL_Event& event);
	virtual void update();
	void cambioTextura(Texture* t);
	void disparar();
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();
	void loadFromFile();
	void saveToFile();
	void setItList(list<GameObject*>::iterator it);
};


