#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include "Game.h"

using namespace std;

class GameState {
private:

protected:
	list<GameObject*> escenario;
	Game* g;

public:
	GameState();
	~GameState();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvents() = 0;

};