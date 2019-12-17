#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"
#include "MenuButton.h"

using namespace std;
class App;

class MainMenuState : public GameState {
private:
	GameObject* aux;
	Texture* fondo;
	SDL_Rect obj;
public:
	MainMenuState(App* a);
	virtual ~MainMenuState();

	virtual void render();
	virtual void update();
	virtual void handleEvent();

	static void menuToPlay(App* app);
	static void exitFromMenu(App* app);
	static void loadFromMenu(App* app);
};