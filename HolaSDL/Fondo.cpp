#include "Fondo.h"
#include "App.h"

Fondo::Fondo(App* a)
{
	app = a;
	textura = a->returnTexture(background0);
	frameDestino.w = textura->getW();
	frameDestino.h = textura->getH();
	frameDestino.x = frameDestino.y = 0;
}

Fondo::~Fondo()
{
}

void Fondo::render()
{
	textura->render(frameDestino, SDL_FLIP_NONE);
}
