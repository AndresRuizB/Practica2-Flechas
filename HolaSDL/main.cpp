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

	/*
	Game* game = new Game();
	
	int resp;
	cout << "Que quieres: jugar(1) o cargar partida(2)\n";
	cin >> resp;

	if (resp == 2) {
		string archivo;
		cout << "Dime el codigo de tu archivo: ";
		cin >> archivo;
		try { game->cargarPartida(archivo + ".txt"); }
		catch (FileNotFoundError e) { cout <<"Error al intentar acceder al arvhivo de guatdado. "<< e.what(); }
		//cargar parida
	}
	
	if (!game->run()) {
		int puntuacion = game->returnPuntuacion();
		delete game;
		try { manageRecords(puntuacion); }
		catch (FileFormatError e) { cout << e.what(); }
		catch (FileNotFoundError e) { cout << e.what(); }
	}//devuelve true si se ha guardado la partida
	*/

	App* aplicacion = new App();

	aplicacion->run();


	return 0;
}