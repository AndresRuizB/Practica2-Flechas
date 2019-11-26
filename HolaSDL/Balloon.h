#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"
#include <list>
#include <fstream>

using namespace std;

class Game;

class Balloon : public ArrowsGameObject
{
private:					//se puede quitar¿?
	bool pinchado = false, nuevoGlobo = false;
	int momentoPinchado;
	int globo; //que sprite de globo tiene

	SDL_Rect frameDestino; //donde va a ser pintado
	int globosPinchadosTemp, globosPinchados;

public:	
	Balloon(Texture* t, Game* g);
	~Balloon();
	void update();
	void render();
	double returnY();
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();
	void loadFromFile();
	void saveToFile(ofstream* output);
	void setItList(list<GameObject*>::iterator it);
};
