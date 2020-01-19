#include "PauseState.h"

PauseState::PauseState(App* a)
{
	app = a;

	aux = new MenuButton(a, this, a->returnTexture(playbutton), 100, 230, resume);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));
	
	aux = new MenuButton(a, this, a->returnTexture(savebutton), 350, 230, save);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	aux = new MenuButton(a, this, a->returnTexture(backbutton), 600, 230, exit);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	fondo = app->returnTexture(background0);
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
}

PauseState::~PauseState()
{
}

void PauseState::update()
{

}


void PauseState::resume(App* app)
{
	app->continueGame();
}

void PauseState::save(App* app)
{
	app->saveGame();
}

void PauseState::exit(App* app)
{
	app->volverMenu();
}
