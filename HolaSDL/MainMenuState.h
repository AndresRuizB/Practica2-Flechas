#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"
#include "Fondo.h"

using namespace std;

class MainMenuState : public GameState {
private:
	App* app;
public:
	Fondo* fondo;
	MainMenuState(App* a);
	~MainMenuState();

	void render();
	void update();
	void handleEvent();
	virtual string getStateID()const { return "Main MenuState"; };
};