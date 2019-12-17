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
}
ArrowsGameObject::~ArrowsGameObject()
{
}

void ArrowsGameObject::loadFromFile(ifstream* input) {
	int x, y;
	*input >> x;
	*input >> y;
	direccion = Vector2D(x, y);
	SDLGameObject::loadFromFile(input);
}

void ArrowsGameObject::saveToFile(ofstream* output) {
	*output << direccion.GetX() << " " << direccion.GetY() << "\n";
	SDLGameObject::saveToFile(output);
}