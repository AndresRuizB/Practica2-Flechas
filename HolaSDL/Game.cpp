﻿#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Game.h"
#include <iostream>
#include "Vector2D.h"
#include "ScoreBoard.h"
#include <iterator>
#include <list>
#include "Arrows_Excepciones.h"
#include <fstream>

using namespace std;

Game::Game() {
	// We ﬁrst initialize SDL
	try {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Ejercicio 3 SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == nullptr || renderer == nullptr)  throw SDLError("No se creo la ventana o el renderer correctamente");
	}
	catch (SDLError& e) { cout << e.what() << endl; }
	catch (exception& e) { cout << e.what() << endl; }

	//creacion de las texturas
	for (int i = 0; i < texturesInfo.size(); i++) {
		textures[i] = new Texture(renderer, texturesInfo[i].direccion, texturesInfo[i].columnas, texturesInfo[i].filas);
	}

	//creacion del arco
	arco = new Bow(textures[bowUncharged], this);
	objetos.push_back(arco);
	hEventsObjetos.push_back(static_cast<Bow*>(arco));

	numMariposas = levelsInfo[NIVEL_INICIAL].nMariposas;
	nivelActual = NIVEL_INICIAL;

	numFlechas = FLECHAS_INICIALES; //numero de flechas iniciales
	puntuacion = 0; //puntuacion inicial

	scoreBoard = new ScoreBoard(textures[digits], textures[arrowUI]); //creacion de la ui

	pasoNivelPorReward = false;
}

Game::~Game() { //destructora
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	for (list<GameObject*>::iterator it = objetos.begin(); it != objetos.end(); it++) {	//el arco se elimina a parte (DONDE¿?)
		delete* it;
	}
	objetos.clear();
	delete scoreBoard;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::run() {
	int startTime, frameTime;
	scoreBoard->actualizaFlechas(numFlechas);//inicializa el numero de flechas

	if (!haSigoCargado)generaMariposas(levelsInfo[nivelActual].nMariposas);

	while (!exit) { // mientras se este jugando
		startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - startTime; //tiempo transquirrido durante el frame
		//es 1000 por que 1 segundo son 1000 milisegundos
		if (frameTime < (1000 / FRAME_RATE)) SDL_Delay((1000 / FRAME_RATE) - frameTime); //se actualiza según la constante FRAME_RATE 
	} //bucle de juego


	if (guardar) guardarPartida();

	return guardar;
}

void Game::update() { //avisa a los objetos para que se actualicen
	//cout << "Obj: " << objetos.size() <<endl;	

	for (list<GameObject*>::iterator it = objetos.begin(); it != objetos.end(); ++it) {
		(*it)->update();
	}

	eliminaObjsUpdate();
	generaGlobo();
	condicionFinDeJuego();
	if (puntuacion >= levelsInfo[nivelActual].puntosSigNivel || pasoNivelPorReward)cambiaNivel();
}

void Game::render()  const {
	SDL_RenderClear(renderer); //limpia la pantalla

	SDL_RenderCopy(renderer, textures[nivelActual + 7]->getTexture(), nullptr, nullptr); //rendariza el fondo

	for (list<GameObject*>::const_iterator it = objetos.begin(); it != objetos.end(); ++it)(*it)->render();

	scoreBoard->render(); //renderiza la ui

	SDL_RenderPresent(renderer); //pinta en pantalla
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true; //si se cierra
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {
			exit = true;
			guardar = true;
		}
		else {
			for (list<EventHandler*>::iterator it = hEventsObjetos.begin(); it != hEventsObjetos.end(); ++it) {
				(*it)->handleEvent(event);
			}
		}
	}
}

void Game::disparar(Arrow* r) {
	if (numFlechas > 0) { //si quedan flechas
		objetos.push_back(r); //lista gameobjects
		list<GameObject*>::iterator it = objetos.end();
		r->setItList(--it);

		flechasObjetos.push_back(r);//lista flechas
		list<Arrow*>::iterator itF = flechasObjetos.end();
		r->setItListFlechas(--itF);

		numFlechas--;
		scoreBoard->actualizaFlechas(numFlechas); //elimina una flecha de la ui
		cout << "Flechas disponibles: " << numFlechas << "\n";
	}
}

//funcion sobrecargada para los globos unicamente (para poder contar cuantos lleva cada flecha)
bool Game::colision(SDL_Rect* globoC, int& numHits) {
	bool colision = false;
	list<Arrow*>::iterator it = flechasObjetos.begin();
	while (!colision && it != flechasObjetos.end()) { //mientras no hay colision y siguen quedando flechas por revisar
		colision = SDL_HasIntersection(globoC, &(*it)->getCollisionRect()); //mira si hay colision
		if (colision) numHits = (*it)->explotoUnGlobo();
		++it;
	}
	return colision; //devulve si ha habido colision
}

//funcion para el resto de objetos
bool Game::colision(SDL_Rect* globoC) {
	bool colision = false;
	list<Arrow*>::iterator it = flechasObjetos.begin();
	while (!colision && it != flechasObjetos.end()) { //mientras no hay colision y siguen quedando flechas por revisar
		colision = SDL_HasIntersection(globoC, &(*it)->getCollisionRect()); //mira si hay colision
		++it;
	}
	return colision; //devulve si ha habido colision
}

void Game::condicionFinDeJuego() {
	if (numFlechas <= 0
		&& flechasObjetos.size() == 0
		|| numMariposas <= 0) exit = true; //condicion de fin de juego
}

void Game::generaGlobo() {
	int probGlobo = rand() % 1000 + 1;
	if (probGlobo <= PROBABILIDAD_GLOBO) {
		Balloon* glo = new Balloon(textures[balloons], this); //crea el globo		
		objetos.push_back(glo); //añade el globo al vector
		list<GameObject*>::iterator it = objetos.end();
		glo->setItList(--it);
	}//aparece un globo
}

void Game::generaMariposas(int num) {
	for (int i = 0; i < num; i++) {
		crearButterflyReward();
	}
}

//crea una mariposa al hacer click en el reward correspondiente
void Game::crearButterflyReward() {
	Butterfly* bfly = new Butterfly(textures[butterflys], this);
	objetos.push_back(bfly);
	list<GameObject*>::iterator it = objetos.end();
	bfly->setItList(--it);
}

//crea unos cuantos globos al hacer click en el reward correspondiente
void Game::creaGlobosReward()
{
	int prob = rand() % (CANTIDAD_MAX_GLOBOS_REWARD - CANTIDAD_MIN_GLOBOS_REWARD) + CANTIDAD_MIN_GLOBOS_REWARD;
	for (; prob > 0; prob--) {
		Balloon* ball = new Balloon(textures[balloons], this);
		objetos.push_back(ball);
		list<GameObject*>::iterator it = objetos.end();
		ball->setItList(--it);
	}

}


void Game::mataMariposa()
{
	numMariposas--;
}

void Game::pasoNivelReward() {
	pasoNivelPorReward = true; //es un flag para que pueda terminar las actualizaciones antes de cambiar de nivel
}

void Game::cambiaNivel()
{
	if (nivelActual != NUMERO_NIVELES - 1) {
		nivelActual++;
		list<GameObject*>::iterator it = objetos.begin();
		++it;
		//elimina todos los objetos
		for (; it != objetos.end(); ++it) {
			delete* it;
		}

		//limpia todas las listas
		hEventsObjetos.erase(++hEventsObjetos.begin(), hEventsObjetos.end());
		objetos.erase(++objetos.begin(), objetos.end());
		flechasObjetos.clear();
		objPenDestruccion.clear();
		flechasPenDestruccion.clear();

		//crea los objetos para el proximo nivel
		numMariposas = levelsInfo[nivelActual].nMariposas;
		numFlechas += levelsInfo[nivelActual].flechasAlLlegar;
		scoreBoard->actualizaFlechas(numFlechas);
		generaMariposas(levelsInfo[nivelActual].nMariposas);

		pasoNivelPorReward = false; //reestablece el valor
	}
}

void Game::actualizaPuntuacion(int puntos) {
	puntuacion += puntos;
	if (puntuacion < 0) puntuacion = 0;
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

void Game::killObject(list<GameObject*>::iterator it) {
	objPenDestruccion.push_back(it); //añade el objeto a la destruccion
}

void Game::killObjectEventHandler(list<EventHandler*>::iterator it) {
	objPenDestruccionEvent.push_back(it);
}

void Game::killObjectFlecha(list<Arrow*>::iterator it)
{
	flechasPenDestruccion.push_back(it);
}

void Game::createReward(int x, int y) {
	int probabilidad = rand() % 100; //genera una probabilidad
	if (probabilidad <= PROBABILIDAD_REWARD) {
		Reward* rew = new Reward(textures[reward], this, textures[burbuja], x, y); //crea el reward
		objetos.push_back(rew);
		list<GameObject*>::iterator it = objetos.end();
		rew->setItList(--it);
		hEventsObjetos.push_back(rew);
		list<EventHandler*>::iterator iter = hEventsObjetos.end(); //lo añade a las listas correspondientes para ser actualizado mas alante
		rew->setItListEventHandler(--iter);
	}
}

void Game::sumaFlechas() {
	numFlechas += SUMA_FLECHAS;
	scoreBoard->actualizaFlechas(numFlechas);//inicializa el numero de flechas
}

void Game::eliminaObjsUpdate()
{
	//objetos pendientes de destruccion
	for (list<list<GameObject*>::iterator>::iterator it = objPenDestruccion.begin(); it != objPenDestruccion.end(); ++it) {
		delete** it;
		objetos.erase(*it);
	}

	//flechas pendientes de destruccion
	for (list<list<Arrow*>::iterator>::iterator it = flechasPenDestruccion.begin(); it != flechasPenDestruccion.end(); it++) {
		flechasObjetos.erase(*it);
	}

	//rewards pendientes de destrucuion
	for (list<list<EventHandler*>::iterator>::iterator it = objPenDestruccionEvent.begin(); it != objPenDestruccionEvent.end(); ++it) {
		hEventsObjetos.erase(*it);
	}

	//limpia las listas
	objPenDestruccionEvent.clear();
	objPenDestruccion.clear();
	flechasPenDestruccion.clear();

}

void Game::guardarPartida() {
	string numPartida;
	cout << "Escribe el codigo de partida: ";
	cin >> numPartida;


	ofstream output;
	output.open(numPartida + ".txt");

	if (output.fail()) throw FileNotFoundError("Error al guardar los records ", numPartida + ".txt");

	output << "game\n";
	output << numMariposas << "\n";
	output << nivelActual << "\n";
	output << puntuacion << "\n";
	output << numFlechas << "\n";
	//output << objetos.size() << "\n";

	for (list<GameObject*>::iterator it = objetos.begin(); it != objetos.end(); ++it) {
		(*it)->saveToFile(&output);
	}

	output.close();
}

void Game::cargarPartida(string file) {
	ifstream input;
	input.open(file);

	if (input.fail()) throw FileNotFoundError("Error al cargar los records ", file);

	string line;

	while (input >> line) {

		if (line == "game") {
			input >> numMariposas;
			input >> nivelActual;
			input >> puntuacion;
			input >> numFlechas;
		}
		else if (line == "bow") {
			arco->loadFromFile(&input);
		}
		else if (line == "baloon") {
			Balloon* glo = new Balloon(textures[balloons], this); //crea el globo		
			objetos.push_back(glo); //añade el globo al vector
			list<GameObject*>::iterator it = objetos.end();
			glo->setItList(--it);
			glo->loadFromFile(&input);
		}
		else if (line == "arrow") {
			Arrow* r = new Arrow(returnPuntTextura(arrowPhysics), this);
			objetos.push_back(r); //lista gameobjects
			list<GameObject*>::iterator it = objetos.end();
			r->setItList(--it);

			flechasObjetos.push_back(r);//lista flechas
			list<Arrow*>::iterator itF = flechasObjetos.end();
			r->setItListFlechas(--itF);

			r->loadFromFile(&input);

		}
		else if (line == "reward") {
			Reward* rew = new Reward(textures[reward], this, textures[burbuja], 0, 0); //crea el reward
			objetos.push_back(rew);
			list<GameObject*>::iterator it = objetos.end();
			rew->setItList(--it);
			hEventsObjetos.push_back(rew);
			list<EventHandler*>::iterator iter = hEventsObjetos.end(); //lo añade a las listas correspondientes para ser actualizado mas alante
			rew->setItListEventHandler(--iter);

			rew->loadFromFile(&input);
		}
		else if (line == "butterfly") {
			Butterfly* bfly = new Butterfly(textures[butterflys], this);
			objetos.push_back(bfly);
			list<GameObject*>::iterator it = objetos.end();
			bfly->setItList(--it);
			bfly->loadFromFile(&input);
		}
	}

	input.close();

	haSigoCargado = true; //dice si se ha cargado la partida
}