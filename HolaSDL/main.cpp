#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "GameStateMachine.h"
#include "App.h"
using namespace std;

using uint = unsigned int;


int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	App* aplicacion = new App();

	aplicacion->run();

	delete aplicacion;
	return 0;
}