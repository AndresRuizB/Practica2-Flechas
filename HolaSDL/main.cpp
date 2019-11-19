#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
#include "Scores.h"

using namespace std;

using uint = unsigned int;

void manageRecords(int puntuaicon) { //se procesa todo el tema de los records
	Scores* scores = new Scores();

	scores->load("top.txt"); //carga todos los records anteriores de archivo
	string name;
	cout << "\n\nCual es tu nombre: \n";
	getline(cin, name);
	if (scores->addScore(name, puntuaicon)) { //si has entrado en el top actualiza el archivo
		scores->save("top.txt");
	}
	else cout << "Lo siento " << name << " no has entrado en el top 10\n"; //si no has entrado en el top

	scores->print(); //muestra los leaderboards por consola

	delete scores;
}

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game* game = new Game();
	game->run();
	int puntuaicon = game->returnPuntuacion();
	delete game;
	manageRecords(puntuaicon);
	return 0;
}