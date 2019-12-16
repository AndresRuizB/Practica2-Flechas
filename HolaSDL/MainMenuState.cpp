#include "MainMenuState.h"
#include "App.h"

MainMenuState::MainMenuState(App* a)
{
	app = a;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render() 
{	
	cout << "render MainMenu \n";
}

void MainMenuState::update() {
	cout << "update MainMenu \n";
}

void MainMenuState::handleEvent()
{
	cout << "hEvents MainMenu \n";
}
