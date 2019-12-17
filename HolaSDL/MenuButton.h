#pragma once
#include "SDLGameObject.h"
#include "EventHandler.h"
#include "Texture.h"
#include "App.h"

class GameState;


class MenuButton:public  SDLGameObject, public EventHandler
{
private:
	Boton tipoBoton;
	SDL_Rect framedestino;
	GameState* gState;

public:
	MenuButton(App* a, GameState* g, int x, int y, Boton b);
	~MenuButton();

	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event& event);
	virtual void saveToFile(ofstream* output) {};
	virtual void loadFromFile(ifstream* input) {};

};