#include "GameStateMachine.h"

GameStateMachine::GameStateMachine()
{
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
	currentState()->render();
}
