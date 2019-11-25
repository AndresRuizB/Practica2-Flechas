#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "ArrowsGameObject.h"
#include <list>

class Arrow:public ArrowsGameObject
{
private:	
	int  velocidad;
	Texture* textura;
	double angulo;
	Game* game;
	list<Arrow*>::iterator posEnEstrFlechas;
	int numGlobosExplotados;

public:
	Arrow(Texture* t, Game* g);
	~Arrow();
	void render();
	void estableceVel(int vel);
	void update();
	void establecePos(Vector2D pos);
	void estableceAng(double ang);
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();
	void loadFromFile();
	void saveToFile();
	void setItList(list<GameObject*>::iterator it);
	void setItListFlechas(list<Arrow*>::iterator it);
	int explotoUnGlobo();
};