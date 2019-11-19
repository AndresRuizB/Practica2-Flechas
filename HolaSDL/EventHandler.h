#pragma once
#include "checkML.h"
#include "SDL.h"

class EventHandler
{
private:
public:
	EventHandler();
	virtual ~EventHandler();
	virtual void handleEvent(SDL_Event& event) = 0;
};