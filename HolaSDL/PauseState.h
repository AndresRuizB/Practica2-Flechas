#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"
#include "MenuButton.h"

using namespace std;
class App;

class PauseState :public GameState //hereda de gameState
{
private:
	GameObject* aux;
	Texture* fondo;
	SDL_Rect obj;
	bool continuePlaying = false;

public:
	PauseState(App* a);
	virtual ~PauseState();

	virtual void update();
	virtual void render();
	virtual void handleEvent();

	static void resume(App* app);
	static void save(App* app);
	static void exit(App* app);
};