#include "PlayState.h"
#include "app.h"

PlayState::PlayState(App* a)
{
	app = a;
}

PlayState::~PlayState()
{
}

void PlayState::update()
{
	cout << "Update PlayState \n";
}

void PlayState::render()
{
	cout << "render PlayState \n";
	SDL_Rect obj;
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
	app->returnTexture(background1)->render(obj);
}

void PlayState::handleEvent()
{
	cout << "handleEvents PlayState \n";
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {

			app->popStateApp();
		}
	}
}


