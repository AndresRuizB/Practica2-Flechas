#include "PlayState.h"
#include "app.h"
#include "Game.h"

PlayState::PlayState(App* a)
{
	app = a;
	//creacion del juego
	game = new Game(app);
}

PlayState::PlayState(App* a, string archivo)
{
	cout << "Cargado de archivo \n";
	game = new Game(a);
	try { game->cargarPartida(archivo + ".txt"); }
	catch (FileNotFoundError e) { cout << "Error al intentar acceder al arvhivo de guatdado. " << e.what(); }
}

PlayState::~PlayState()
{
	delete game;
}

void PlayState::update()
{
	game->update();
}

void PlayState::render()
{
	game->render();
	SDL_Rect obj;
}

void PlayState::handleEvent()
{
	game->handleEvents();
}

int PlayState::returnPuntuacion()
{
	return game->returnPuntuacion();
}

void PlayState::save()
{
	game->guardarPartida();
}


