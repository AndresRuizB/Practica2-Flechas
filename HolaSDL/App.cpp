#include "App.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"

App::App()
{
	try {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Ejercicio 3 SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == nullptr || renderer == nullptr)  throw SDLError("No se creo la ventana o el renderer correctamente");
	}
	catch (SDLError& e) { cout << e.what() << endl; }
	catch (exception& e) { cout << e.what() << endl; }

	for (int i = 0; i < texturesInfo.size(); i++) {
		textures[i] = new Texture(renderer, texturesInfo[i].direccion, texturesInfo[i].columnas, texturesInfo[i].filas);
	}

	maquinaEstados = new GameStateMachine(renderer);
	maquinaEstados->pushState(new MainMenuState(this));
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

Texture* App::returnTexture(OBJETOS obj)
{
	return textures[obj];
}

void App::pushStateApp(GameState* gState)
{
	maquinaEstados->pushState(gState);
}

void App::popStateApp()
{
	maquinaEstados->popState();
}
