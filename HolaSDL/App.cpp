#include "App.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"


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
	cout << "Destructora app";
	delete maquinaEstados;
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	salir();
}

void App::run()
{
	int startTime, frameTime;
	while (!exit) { //ves este true, esta noche explotara por esto y no sabremos xq, guarda el tweet
		startTime = SDL_GetTicks();
		maquinaEstados->handleEvent();
		maquinaEstados->update();
		maquinaEstados->render();

		if (menuPlay) {
			if (load) {
				string archivo;
				cout << "Dime el codigo de tu archivo: ";
				cin >> archivo;
				maquinaEstados->changeState(new PlayState(this, archivo));
				load = false;
			}
			else maquinaEstados->changeState(new PlayState(this));
			menuPlay = false;
		}
		else if (vMenu) {
			popStateApp();
			maquinaEstados->pushState(new MainMenuState(this));
			vMenu = false;
		}
		else if (contGame) {
			popStateApp();
			contGame = false;

			if (save) { //llamar al game q guarde
				maquinaEstados->currentState()->save();
				exit = true;
			}
		}

		frameTime = SDL_GetTicks() - startTime; //tiempo transquirrido durante el frame
		if (frameTime < (1000 / FRAME_RATE)) SDL_Delay((1000 / FRAME_RATE) - frameTime); //se actualiza según la constante FRAME_RATE 
	}

	popStateApp();
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

void App::menuToPlay()
{
	menuPlay = true;
}

void App::volverMenu()
{
	vMenu = true;
}

void App::salir()
{
	exit = true;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void App::pausa()
{
	maquinaEstados->pushState(new PauseState(this));
}

void App::continueGame()
{
	contGame = true;
}

void App::endGame()
{
	puntuacion = dynamic_cast<PlayState*>(maquinaEstados-> currentState())->returnPuntuacion();
	popStateApp();
	EndState* eState = new EndState(this);
	maquinaEstados->pushState(eState);
	eState->Records(puntuacion);
}

void App::saveGame()
{
	contGame = true;
	save = true;
}

void App::loadGame()
{
	menuPlay = true;
	load = true;
}
