#include "MenuButton.h"
#include "Texture.h"
#include "App.h"
#include "GameState.h"

MenuButton::MenuButton(App* a, GameState* g, Texture* t, int x, int y,  void (*cb)())
{
	textura = t;

	ancho = textura->getW();
	alto = textura->getH();

	gState = g;

	framedestino.h = alto / 5;
	framedestino.w = ancho / 5;
	framedestino.x = x;
	framedestino.y = y;

	mCallback = cb;
}

MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	textura->render(framedestino, SDL_FLIP_NONE);
}

void MenuButton::update()
{
}

void MenuButton::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		SDL_Point punto;

		punto.x = x;
		punto.y = y;

		if (SDL_PointInRect(&punto, &framedestino)) {			
			mCallback();
		}
	}
}
