#include "EndState.h"
#include "MenuButton.h"

#include <iterator>

EndState::EndState(App* a)
{
	app = a;
	aux = new MenuButton(a, this, a->returnTexture(backbutton), 250, 230, retunToMenu);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	aux = new MenuButton(a, this, a->returnTexture(exitbutton), 500, 230, exit);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	fondo = app->returnTexture(background0);
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
}

EndState::~EndState()
{
}

void EndState::render()
{
	fondo->render(obj);
	for (list<GameObject*>::const_iterator it = escenario.begin(); it != escenario.end(); ++it) (*it)->render();
}

void EndState::update()
{
}

void EndState::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (list<EventHandler*>::const_iterator it = manejadoresEventos.begin(); it != manejadoresEventos.end(); ++it)(*it)->handleEvent(event);
	}
}

void EndState::exit(App* app)
{
	app->salir();
}

void EndState::retunToMenu(App* app)
{
	app->volverMenu();
}
