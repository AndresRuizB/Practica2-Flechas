#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include "Game.h"
#include "EventHandler.h"

using namespace std;

class GameState {
private:

protected:
	list<GameObject*> escenario;
	list<EventHandler*> manejadoresEventos;
	Game* g;

public:
	GameState();
	~GameState();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvent() = 0;

};