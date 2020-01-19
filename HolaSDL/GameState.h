#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include "SDL.h"
#include "SDL_image.h"
#include "texture.h"

class GameStateMachine;
class App;

using namespace std;
using CallBack = void(App* app);

class GameState {
private:

protected:
	list<GameObject*> escenario;
	list<EventHandler*> manejadoresEventos;
	SDL_Renderer* renderer;
	App* app;
	bool menu = false;


	Texture* fondo;
	SDL_Rect obj;

public:
	GameState();
	virtual ~GameState();

	virtual void render();
	virtual void update() = 0;
	virtual void handleEvent();
	virtual void save() {};
};