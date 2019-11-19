#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Game.h"
#include <iostream>
#include "Vector2D.h"
#include "ScoreBoard.h"

using namespace std;

Game::Game() {
	// We ﬁrst initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Ejercicio 3 SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)  throw "Error loading the SDL window or renderer";

	//creacion de las texturas
	for (int i = 0; i < texturesInfo.size(); i++) {
		textures[i] = new Texture(renderer, texturesInfo[i].direccion, texturesInfo[i].columnas, texturesInfo[i].filas);
	}

	//creacion del arco
	arco = new Bow(textures[5], this);
	objetos.push_back(arco); //guarda en arco en el array de objetos

	numFlechas = FLECHAS_INICIALES; //numero de flechas iniciales
	puntuacion = 0; //puntuacion inicial

	scoreBoard = new ScoreBoard(textures[6], textures[1]); //creacion de la ui
}

Game::~Game() { //destructora
	delete arco; //se destruyen todos los objetos del juego
	objetos.erase(objetos.begin()); //quita al arco del vector
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	for (int i = 0; i < objetos.size(); i++) delete objetos[i];
	//for (int i = 0; i < globos.size(); i++) delete globos[i];
	//for (int i = 0; i < flechas.size(); i++) delete flechas[i];
	delete scoreBoard;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	int startTime, frameTime;
	scoreBoard->actualizaFlechas(numFlechas);//inicializa el numero de flechas
	while (!exit) { // mientras se este jugando
		startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - startTime; //tiempo transquirrido durante el frame
		//es 1000 por que 1 segundo son 1000 milisegundos
		if (frameTime < (1000 / FRAME_RATE)) SDL_Delay((1000 / FRAME_RATE) - frameTime); //se actualiza según la constante FRAME_RATE 
	} //bucle de juego

}

void Game::update() { //avisa a los objetos para que se actualicen

	for (int i = 0; i < objetos.size();i++) {	
		if (!objetos[i]->update()) { //desaparece el objeto

			if (typeid(*objetos[i]) == typeid(Arrow))destruyeFlecha(objetos[i]);

			delete objetos[i];
			objetos.erase(objetos.begin()+i);
			cout << "\nobjeto destruido\n";
			i--;
		}
	}

	generaGlobo();
	condicionFinDeJuego();
}

void Game::render() const {
	SDL_RenderClear(renderer); //limpia la pantalla

	SDL_RenderCopy(renderer, textures[3]->getTexture(), nullptr, nullptr); //rendariza el fondo

	for (int i = 0; i < objetos.size(); i++) objetos[i]->render(); 

	scoreBoard->render(); //renderiza la ui

	SDL_RenderPresent(renderer); //pinta en pantalla
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true; //si se cierra
		else {
			static_cast<Bow*>(arco)->handleEvent(event); //los eventos del arco
		}
	}
}

void Game::disparar(Arrow* r) {
	if (numFlechas > 0) { //si quedan flechas
		objetos.push_back(r); 
		flechasObjetos.push_back(r);
		numFlechas--;
		scoreBoard->actualizaFlechas(numFlechas); //elimina una flecha de la ui
		cout << "Flechas disponibles: " << numFlechas << "\n";
	}
}

bool Game::colision(SDL_Rect* globoC) {
	bool colision = false;
	int cont = 0;
	while (!colision && cont < flechasObjetos.size()) { //mientras no hay colision y siguen quedando flechas por revisar
		colision = SDL_HasIntersection(globoC, &flechasObjetos[cont]->getCollisionRect()); //mira si hay colision
		cont++;
	}
	return colision; //devulve si ha habido colision
}

void Game::condicionFinDeJuego() {
	if (numFlechas <= 0 && flechasObjetos.size() == 0) exit = true; //condicion de fin de juego
}

void Game::generaGlobo() {
	int probGlobo = rand() % 1000 + 1;
	if (probGlobo <= PROBABILIDAD_GLOBO) {
		Balloon* glo = new Balloon(textures[2], this); //crea el globo
		objetos.push_back(glo); //añade el globo al vector
	}//aparece un globo
}

void Game::actualizaPuntuacion() {
	puntuacion += PUNTUACION_POR_GLOBO;
	cout << "Puntuacion: " << puntuacion << "\n";
	scoreBoard->actualizaPuntuacion(puntuacion); //actualiza la puntuacion en pantalla
}

int Game::returnPuntuacion() {
	return puntuacion;
}

int Game::returnNumFlechas() {
	return numFlechas;
}

//devuelve un puntero a la textura seleccionada
Texture* Game::returnPuntTextura(int indice) {
	return textures[indice];
}

/*void Game::killObject(vector<GameObject*>::iterator it) {
	objPenDestruccion.push_back(it);
}*/

void Game::destruyeFlecha(GameObject* f) {
	bool encontrado = false;
	int i = 0;

	while (!encontrado && i < flechasObjetos.size()) { //busca la flecha dada para eliminarla de su array
		if (flechasObjetos[i] == f) {
			flechasObjetos.erase(flechasObjetos.begin()); //si es flecha destruye la primera flecha
			encontrado = true;
		}
	}	
}