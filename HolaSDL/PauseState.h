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
	bool continuePlaying = false;

public:
	PauseState(App* a);
	virtual ~PauseState();

	virtual void update();

	static void resume(App* app);
	static void save(App* app);
	static void exit(App* app);
};