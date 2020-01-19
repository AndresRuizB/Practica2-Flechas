#include "GameState.h"

GameState::GameState()
{

}

GameState::~GameState()
{
	for (list<GameObject*>::iterator it = escenario.begin(); it != escenario.end(); ++it)delete* it;

	escenario.clear();
	manejadoresEventos.clear();
}

void GameState::render() {
	fondo->render(obj);
	for (list<GameObject*>::const_iterator it = escenario.begin(); it != escenario.end(); ++it) (*it)->render();
}

void GameState::handleEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (list<EventHandler*>::const_iterator it = manejadoresEventos.begin(); it != manejadoresEventos.end(); ++it)(*it)->handleEvent(event);
	}
}