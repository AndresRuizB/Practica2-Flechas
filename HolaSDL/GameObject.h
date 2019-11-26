#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Arrows_Excepciones.h"
#include <fstream>

class GameObject
{
private:

protected:

public:
	GameObject(); //constructora vacia
	virtual ~GameObject(); 

	virtual void render() = 0;
	virtual void update() = 0;
	//es comun para todos
	virtual void saveToFile(ofstream* output) = 0;
	virtual void loadFromFile(ifstream* input) = 0;
};

