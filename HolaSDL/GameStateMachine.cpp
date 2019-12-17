#include "GameStateMachine.h"
#include "GameState.h"

GameStateMachine::GameStateMachine(SDL_Renderer* r)
{
	renderer = r;
}

GameStateMachine::~GameStateMachine()
{
	while (!pilaEstados.empty()) {
		delete pilaEstados.top();
		pilaEstados.pop();
	}
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
		delete pilaEstados.top();
		pilaEstados.pop();
	}
	pilaEstados.push(gState);
}

void GameStateMachine::popState()
{
	delete pilaEstados.top();
	pilaEstados.pop();
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
