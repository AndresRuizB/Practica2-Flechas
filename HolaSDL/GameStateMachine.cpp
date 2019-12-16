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
	pilaEstados.pop();
	pilaEstados.push(gState);
}

void GameStateMachine::popState()
{
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
}

void GameStateMachine::handleEvent()
{
	currentState()->handleEvent();
}
