#pragma once
#include <stack>
#include "GameState.h"

using namespace std;

class GameStateMachine {
private:

	stack<GameState*> pilaEstados;
	SDL_Renderer* renderer;

public:

	GameStateMachine(SDL_Renderer* renderer);
	~GameStateMachine();

	GameState* currentState();


	void pushState(GameState* gState);
	void changeState(GameState* gState);
	void popState();

	void update();
	void render();
	void handleEvent();
};