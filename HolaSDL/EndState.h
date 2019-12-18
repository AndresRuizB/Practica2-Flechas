#pragma once
#include "GameStateMachine.h"
#include "SDLGameObject.h"
#include "MenuButton.h"

using namespace std;
class App;

class EndState : public GameState {
private:
	GameObject* aux;
	Texture* fondo;
	SDL_Rect obj;
public:
	EndState(App* a);
	virtual ~EndState();

	virtual void render();
	virtual void update();
	virtual void handleEvent();

	void Records(int puntuacion);

	static void exit(App* app);
	static void retunToMenu(App* app);
};