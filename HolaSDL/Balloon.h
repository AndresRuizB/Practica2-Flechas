#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"

using namespace std;

class Game;

class Balloon : public ArrowsGameObject
{
private:
	bool pinchado = false, nuevoGlobo = false;
	int momentoPinchado;
	int globo; //que sprite de globo tiene

public:

	SDL_Rect frameDestino; //donde va a ser pintado
	Balloon(Texture* t, Game* g);
	~Balloon();
	bool update();
	void render();
	double returnY();
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();
	void loadFromFile();
	void saveToFile();
	void setItList(vector<GameObject*>::iterator it);
};
