#include <vector>
#include <iostream>
#include <iterator>
#include <list>
#include <fstream>

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Game.h"
#include "Vector2D.h"
#include "ScoreBoard.h"
#include "Arrows_Excepciones.h"
#include "App.h"

using namespace std;

Game::Game(App* a) {

	app = a;

	//creacion del arco
	arco = new Bow(app->returnTexture(bowUncharged), this);
	objetos.push_back(arco);
	hEventsObjetos.push_back(static_cast<Bow*>(arco));

	numMariposas = levelsInfo[NIVEL_INICIAL].nMariposas;
	nivelActual = NIVEL_INICIAL;

	numFlechas = FLECHAS_INICIALES; //numero de flechas iniciales
	puntuacion = 0; //puntuacion inicial

	scoreBoard = new ScoreBoard(app->returnTexture(digits), app->returnTexture(arrowUI)); //creacion de la ui
	scoreBoard->actualizaFlechas(numFlechas);//inicializa el numero de flechas

	generaMariposas(levelsInfo[nivelActual].nMariposas);

	pasoNivelPorReward = false;
	fondo = a->returnTexture((OBJETOS)(nivelActual + 7));
	framDestinoFondo.x = framDestinoFondo.y = 0;
	framDestinoFondo.h = fondo->getH();
	framDestinoFondo.w = fondo->getW();
}

Game::~Game() { //destructora
	for (list<GameObject*>::iterator it = objetos.begin(); it != objetos.end(); it++) {	//el arco se elimina a parte (DONDE¿?)
		delete* it;
	}

	objetos.clear();
	delete scoreBoard;
}


void Game::update() { //avisa a los objetos para que se actualicen
	//cout << "Obj: " << objetos.size() <<endl;	

	for (list<GameObject*>::iterator it = objetos.begin(); it != objetos.end(); ++it) {
		(*it)->update();
	}

	eliminaObjsUpdate();
	generaGlobo();
	condicionFinDeJuego();
	if (puntuacion >= levelsInfo[nivelActual].puntosSigNivel || pasoNivelPorReward) cambiaNivel();
	   	 
	if (exit)app->endGame();//pantalla de fin de juego
}

void Game::render()  const {
	fondo->render(framDestinoFondo, SDL_FLIP_NONE);

	for (list<GameObject*>::const_iterator it = objetos.begin(); it != objetos.end(); ++it)(*it)->render();

	scoreBoard->render(); //renderiza la ui
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true; //si se cierra
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) { //pausa
			app->pausa();
		}
		else {//los handle events de todos los objetos q reaccionan a envetntos de la escena
			for (list<EventHandler*>::iterator it = hEventsObjetos.begin(); it != hEventsObjetos.end(); ++it) {
				(*it)->handleEvent(event);
			}
		}
	}
}


void Game::disparar(Arrow* r) {
	cout << "disparar";
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
		Balloon* glo = new Balloon(app->returnTexture(balloons), this); //crea el globo		
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
	Butterfly* bfly = new Butterfly(app->returnTexture(butterflys), this);
	objetos.push_back(bfly);
	list<GameObject*>::iterator it = objetos.end();
	bfly->setItList(--it);
}

//crea unos cuantos globos al hacer click en el reward correspondiente
void Game::creaGlobosReward()
{
	int prob = rand() % (CANTIDAD_MAX_GLOBOS_REWARD - CANTIDAD_MIN_GLOBOS_REWARD) + CANTIDAD_MIN_GLOBOS_REWARD;
	for (; prob > 0; prob--) {
		Balloon* ball = new Balloon(app->returnTexture(balloons), this);
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
		cout << "CAMBIO nivel";
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
		fondo = app->returnTexture((OBJETOS)(nivelActual + 7));
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
	return app->textures[indice];
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
		Reward* rew = new Reward(app->returnTexture(reward), this, app->returnTexture(burbuja), x, y); //crea el reward
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
			fondo = app->returnTexture((OBJETOS)(nivelActual + 7));
			input >> puntuacion;
			input >> numFlechas;
			scoreBoard->actualizaFlechas(numFlechas);//inicializa el numero de flechas
		}
		else if (line == "bow") {
			arco->loadFromFile(&input);
		}
		else if (line == "baloon") {
			Balloon* glo = new Balloon(app->returnTexture(balloons), this); //crea el globo		
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
			Reward* rew = new Reward(app->returnTexture(reward), this, app->returnTexture(burbuja), 0, 0); //crea el reward
			objetos.push_back(rew);
			list<GameObject*>::iterator it = objetos.end();
			rew->setItList(--it);
			hEventsObjetos.push_back(rew);
			list<EventHandler*>::iterator iter = hEventsObjetos.end(); //lo añade a las listas correspondientes para ser actualizado mas alante
			rew->setItListEventHandler(--iter);

			rew->loadFromFile(&input);
		}
		else if (line == "butterfly") {
			Butterfly* bfly = new Butterfly(app->returnTexture(butterflys), this);
			objetos.push_back(bfly);
			list<GameObject*>::iterator it = objetos.end();
			bfly->setItList(--it);
			bfly->loadFromFile(&input);
		}
	}

	input.close();

	haSigoCargado = true; //dice si se ha cargado la partida
}