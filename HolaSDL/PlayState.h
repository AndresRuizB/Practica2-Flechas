#pragma once
#include "GameState.h"

using namespace std;

class PlayState :public GameState //hereda de gameState
{
private:


public:
	void update();
	void render();
	void handleEvent();


};