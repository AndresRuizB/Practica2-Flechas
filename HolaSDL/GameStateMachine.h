#pragma once
#include <stack>
#include "GameState.h"

using namespace std;

class GameStateMachine {
private:

	stack<GameState*> pilaEstados;

public:

	GameStateMachine();
	~GameStateMachine();

	GameState* currentState();
	void pushState(GameState* gState);
	void changeState(GameState* gState);
	void popState();

	void update();
	void render();
};