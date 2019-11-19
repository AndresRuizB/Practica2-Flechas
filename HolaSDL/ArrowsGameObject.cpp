#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "ArrowsGameObject.h"


ArrowsGameObject::ArrowsGameObject() {
	posicion = Vector2D();
	alto = 0;
	ancho = 0;
	direccion = Vector2D();
	textura = nullptr;
	game = nullptr;
}
ArrowsGameObject::~ArrowsGameObject()
{
}
