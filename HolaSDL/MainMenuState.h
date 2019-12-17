#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"

using namespace std;

class MainMenuState : public GameState {
private:
	
public:
	MainMenuState(App* a);
	~MainMenuState();

	void render();
	void update();
	void handleEvent();
};