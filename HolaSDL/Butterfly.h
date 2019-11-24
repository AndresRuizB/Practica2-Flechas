#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"
#include <list>

using namespace std;

class Game;

class Butterfly : public ArrowsGameObject
{
private:
	
	int frame, tiempoMuerta; //para la animación
	bool muerta;

public:

	SDL_Rect frameDestino; //donde va a ser pintado
	Butterfly(Texture* t, Game* g);
	~Butterfly();
	void update();
	void render();
	double returnY();
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();
	void loadFromFile();
	void saveToFile();
	void setItList(list<GameObject*>::iterator it);
};
