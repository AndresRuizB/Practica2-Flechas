#include "MainMenuState.h"
#include "App.h"
#include "Fondo.h"

MainMenuState::MainMenuState(App* a)
{
	app = a;
	fondo = new Fondo(a);
	escenario.push_back(fondo);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render() {	
	fondo->render();
}

void MainMenuState::update() {

}

void MainMenuState::handleEvent()
{

}
