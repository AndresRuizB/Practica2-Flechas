#include "MainMenuState.h"
#include "App.h"
#include "PlayState.h"

MainMenuState::MainMenuState(App* a)
{
	app = a;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render()
{
	cout << "render MainMenu \n";
	SDL_Rect obj;
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
	app->returnTexture(background0)->render(obj);
}

void MainMenuState::update() {
	cout << "update MainMenu \n";

}

void MainMenuState::handleEvent()
{
	cout << "hEvents MainMenu \n";

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
		{
			PlayState* p = new PlayState(app);
			app->pushStateApp(p);
		}
	}
}
