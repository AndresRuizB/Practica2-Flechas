#pragma once

#include <vector>
#include <iterator>
#include <list>

#include "checkML.h"
#include "Texture.h"
#include "Bow.h"
#include "Balloon.h"
#include "Vector2D.h"
#include "Arrow.h"
#include "ScoreBoard.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "Butterfly.h"
#include "Reward.h"
#include "App.h"

using namespace std;

class Game {
private:
	bool exit = false;
	bool guardar = false;
	bool haSigoCargado = false;
	list<GameObject*> objetos;
	list<Arrow*> flechasObjetos;
	list<list<Arrow*>::iterator> flechasPenDestruccion;
	list<EventHandler*> hEventsObjetos;
	list<list<GameObject*>::iterator> objPenDestruccion;
	list<list<EventHandler*>::iterator> objPenDestruccionEvent;

	//informacion a guardar
	int numMariposas;
	int nivelActual;
	int puntuacion, numFlechas;

	GameObject* arco;
	ScoreBoard* scoreBoard;

	bool pasoNivelPorReward;


	SDL_Rect framDestinoFondo;
	Texture* fondo;

	App* app;

public:
	Game(App* a);
	~Game();
	void render() const;
	void handleEvents();
	void update();
	void disparar(Arrow* r);
	bool colision( SDL_Rect* globoC);
	bool colision(SDL_Rect* globoC, int& numHits);
	void actualizaPuntuacion(int puntos);
	void condicionFinDeJuego();
	int returnPuntuacion();
	int returnNumFlechas();
	Texture* returnPuntTextura(int indice);
	void generaGlobo();
	void generaMariposas(int num);
	void mataMariposa();
	void cambiaNivel();
	void killObject(list<GameObject*>::iterator it);
	void killObjectEventHandler(list<EventHandler*>::iterator it);
	void killObjectFlecha(list<Arrow*>::iterator it);
	void createReward(int x, int y);
	void sumaFlechas();
	void eliminaObjsUpdate();
	void pasoNivelReward();
	void guardarPartida();
	void cargarPartida(string file);
	void crearButterflyReward();
	void creaGlobosReward();
};
