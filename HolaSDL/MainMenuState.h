#pragma once
#include "GameStateMachine.h"

using namespace std;

class MainMenuState : public GameState {
private:

public:
	MainMenuState();
	~MainMenuState();

	void render();
	void update();
	void handleEvent();
	virtual string getStateID()const { return "Main MenuState"; };
};