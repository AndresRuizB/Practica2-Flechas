#include "SDLGameObject.h"


void SDLGameObject::loadFromFile(ifstream* input) {
	int x, y;
	*input >> x;
	*input >> y;
	posicion = Vector2D(x, y);
}

void SDLGameObject::saveToFile(ofstream* output) {
	*output << posicion.GetX() << " " << posicion.GetY() << "\n";	
}

