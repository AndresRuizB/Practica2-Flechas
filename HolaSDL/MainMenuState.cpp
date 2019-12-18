#include "MainMenuState.h"
#include "PlayState.h"
#include "MenuButton.h"

#include <iterator>

MainMenuState::MainMenuState(App* a)
{
	app = a;

	//botones
	aux = new MenuButton(a, this, a->returnTexture(playbutton), 100, 230, menuToPlay);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	aux = new MenuButton(a, this, a->returnTexture(loadbutton), 350, 230, loadFromMenu);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	aux = new MenuButton(a, this, a->returnTexture(exitbutton), 600, 230, exitFromMenu);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	fondo = app->returnTexture(background0);
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render()
{
	fondo->render(obj);
	for (list<GameObject*>::const_iterator it = escenario.begin(); it != escenario.end(); ++it) (*it)->render();
}

void MainMenuState::update() {
}

void MainMenuState::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (list<EventHandler*>::const_iterator it = manejadoresEventos.begin(); it != manejadoresEventos.end(); ++it)(*it)->handleEvent(event);
	}
}


void MainMenuState::menuToPlay(App* app)
{
	app->menuToPlay();
}

void MainMenuState::exitFromMenu(App* app)
{
	app->salir();
}

void MainMenuState::loadFromMenu(App* app)
{
	app->loadGame();
}