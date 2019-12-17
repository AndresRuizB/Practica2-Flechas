#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "GameObject.h"

class SDLGameObject : public GameObject {
private:

protected:
	int ancho, alto;
	Texture* textura;
	Vector2D posicion;

public:

	virtual void saveToFile(ofstream* output) ;
	virtual void loadFromFile(ifstream* input) ;
};