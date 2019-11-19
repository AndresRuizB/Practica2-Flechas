#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "GameObject.h"
#include <vector>

class Game;

class ArrowsGameObject : public GameObject {
private:

protected:
	Vector2D posicion;
	int ancho, alto;
	Vector2D direccion;
	Texture* textura;
	Game* game;
	vector<GameObject*>::iterator posicionEnEstructura; 

public:
	ArrowsGameObject();
	virtual ~ArrowsGameObject();

	virtual void render() = 0;
	virtual bool update() = 0;
	virtual SDL_Rect getDestRect() = 0;
	virtual SDL_Rect getCollisionRect() = 0;
	virtual void loadFromFile() = 0;
	virtual void saveToFile() = 0;	
	virtual void setItList(vector<GameObject*>::iterator it) = 0;

};