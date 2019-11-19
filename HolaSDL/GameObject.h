#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>


class GameObject
{
private:

protected:

public:
	GameObject(); //constructora vacia
	virtual ~GameObject(); 

	virtual void render() = 0;
	virtual void update() = 0;
	
};

