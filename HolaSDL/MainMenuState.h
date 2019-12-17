#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"
#include "MenuButton.h"

using namespace std;

class MainMenuState : public GameState {
private:
	
public:
	MainMenuState(App* a);
	~MainMenuState();

	virtual void render();
	virtual void update();
	virtual void handleEvent();
	virtual void playState();
	virtual void exitState();

	static void menuToPlay();
	static void exitFromMenu();
	static void loadFromMenu();
};