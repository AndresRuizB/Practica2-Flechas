#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"
#include "MenuButton.h"

using namespace std;
class App;

class MainMenuState : public GameState {
private:
	GameObject* aux;
public:
	MainMenuState(App* a);
	virtual ~MainMenuState();

	virtual void update();

	static void menuToPlay(App* app);
	static void exitFromMenu(App* app);
	static void loadFromMenu(App* app);
};