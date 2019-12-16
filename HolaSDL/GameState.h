#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include "SDL.h"
#include "SDL_image.h"
#include "texture.h"

class App;

using namespace std;

class GameState {
private:

protected:
	list<GameObject*> escenario;
	list<EventHandler*> manejadoresEventos;
	SDL_Renderer* renderer;
	App* app;
public:
	GameState();
	~GameState();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvent() = 0;

};