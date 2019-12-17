#include "PlayState.h"
#include "app.h"
#include "Game.h"

PlayState::PlayState(App* a)
{
	app = a;
	//creacion del juego
	game = new Game(app);
}

PlayState::~PlayState()
{
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



	/*SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			//app->popStateApp();
		}
	}*/
}


