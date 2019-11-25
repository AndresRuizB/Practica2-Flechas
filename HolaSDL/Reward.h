#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Game.h"

class Reward : public ArrowsGameObject, public EventHandler
{
private:
	Texture* textura;
	Texture* burbuja;
	Game* game;
	Vector2D posicion, direccion;
	SDL_Rect frameDestino; //donde va a ser pintado
	SDL_Rect frameDestinoBurbuja; //donde va a ser pintado
	int tipo_reward, estado_rotacion;
	bool conBurbuja;
	list<EventHandler*>::iterator posicionEnEventos;
	
public:
	Reward(Texture* t, Game* g, Texture* b, int x, int y);
	~Reward();
	virtual void render();
	virtual void update();
	virtual SDL_Rect getDestRect();
	virtual SDL_Rect getCollisionRect();
	virtual void loadFromFile();
	virtual void saveToFile();
	virtual void setItList(list<GameObject*>::iterator it);
	virtual void setItListEventHandler(list<EventHandler*>::iterator it);


	void handleEvent(SDL_Event& event);
};