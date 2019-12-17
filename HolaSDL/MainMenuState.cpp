#include "MainMenuState.h"
#include "App.h"
#include "PlayState.h"
#include "MenuButton.h"

#include <iterator>

MainMenuState::MainMenuState(App* a)
{
	app = a;
	MenuButton* pla = new MenuButton(a, this, a->returnTexture(playbutton), 100, 230, menuToPlay);
	escenario.push_back(pla);
	manejadoresEventos.push_back(pla);

	MenuButton* exi = new MenuButton(a, this, a->returnTexture(exitbutton), 500, 230, exitFromMenu);
	escenario.push_back(exi);
	manejadoresEventos.push_back(exi);

	MenuButton* loa = new MenuButton(a, this, a->returnTexture(loadbutton), 300, 230, loadFromMenu);
	escenario.push_back(loa);
	manejadoresEventos.push_back(loa);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render()
{
	SDL_Rect obj;
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
	app->returnTexture(background0)->render(obj);//todo lo del fondo se podria poner en variables locales y no tener q llamar al app cada frame, solo una vez

	for (list<GameObject*>::const_iterator it = escenario.begin(); it != escenario.end(); ++it)(*it)->render();
}

void MainMenuState::update() {

}

void MainMenuState::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
		{
			playState();
		}
		else {

			for (list<EventHandler*>::const_iterator it = manejadoresEventos.begin(); it != manejadoresEventos.end(); ++it)(*it)->handleEvent(event);
		}
	}
}

void MainMenuState::playState()
{
	PlayState* p = new PlayState(app);
	app->pushStateApp(p);
}

void MainMenuState::exitState()
{
	//funcionar funciona pero como se imprimen muchas cosas por pantalla no se ve nah
	cout << "CERRRAAARRRR SDLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
}

void MainMenuState::menuToPlay()
{
	cout << "Play button clicked\n";
}

void MainMenuState::exitFromMenu()
{
	cout << "Exit button clicked\n";
}

void MainMenuState::loadFromMenu()
{
	cout << "load button clicked\n";
}