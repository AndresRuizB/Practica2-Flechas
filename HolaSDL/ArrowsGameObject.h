#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "SDLGameObject.h"
#include <vector>
#include <list>

class Game;

class ArrowsGameObject : public SDLGameObject {
private:

protected:
	list<GameObject*>::iterator posicionEnEstructura;

	Vector2D direccion;
	SDL_Rect frameDestino;

public:
	ArrowsGameObject();
	virtual ~ArrowsGameObject();

	virtual SDL_Rect getDestRect() = 0;
	virtual SDL_Rect getCollisionRect() = 0;
	virtual void setItList(list<GameObject*>::iterator it) = 0;

};