#include "App.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"

App::App()
{
	for (int i = 0; i < texturesInfo.size(); i++) {
		textures[i] = new Texture(renderer, texturesInfo[i].direccion, texturesInfo[i].columnas, texturesInfo[i].filas);
	}

	maquinaEstados = new GameStateMachine();
	maquinaEstados->pushState(new MainMenuState);
}

App::~App()
{
	delete maquinaEstados;
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
}

void App::run()
{
	while (true) { 
		maquinaEstados->handleEvent();
		maquinaEstados->update();
		maquinaEstados->render();
	}
}
