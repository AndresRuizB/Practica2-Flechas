#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include "EventHandler.h"

class App;

using namespace std;

class GameState {
private:

protected:
	list<GameObject*> escenario;
	list<EventHandler*> manejadoresEventos;
	App* app;

public:
	GameState();
	~GameState();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvent() = 0;

};