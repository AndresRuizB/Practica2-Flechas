#pragma once
#include "GameState.h"
#include "Game.h"

using namespace std;
class App;

class PlayState :public GameState //hereda de gameState
{
private:
	Game* game;

public:
	PlayState(App* a);
	virtual ~PlayState();

	virtual void update();
	virtual void render();
	virtual void handleEvent();
};