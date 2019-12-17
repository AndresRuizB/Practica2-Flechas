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
