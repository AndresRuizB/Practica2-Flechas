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
	Arrow* flecha;

	bool cargado;
	double angulo;
	float velFlecha;

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
	void saveToFile(ofstream* output);
	void setItList(list<GameObject*>::iterator it);
};


