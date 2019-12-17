#include "GameStateMachine.h"
#include "GameState.h"

GameStateMachine::GameStateMachine(SDL_Renderer* r)
{
	renderer = r;
}

GameStateMachine::~GameStateMachine()
{
}

GameState* GameStateMachine::currentState()
{
	return pilaEstados.top();
}

void GameStateMachine::pushState(GameState* gState)
{
	pilaEstados.push(gState);
}

void GameStateMachine::changeState(GameState* gState)
{
	if (!pilaEstados.empty()) {
		pilaEstados.pop();
	}
	pilaEstados.push(gState);
}

void GameStateMachine::popState()
{
	if (pilaEstados.size()>1) {
		pilaEstados.pop();
	}
}

void GameStateMachine::update()
{
	currentState()->update();
}

void GameStateMachine::render()
{
	SDL_RenderClear(renderer);
	currentState()->render();
	SDL_RenderPresent(renderer);
}

void GameStateMachine::handleEvent()
{
	currentState()->handleEvent();
}
