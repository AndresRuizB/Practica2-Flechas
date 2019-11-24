#pragma once

#include "Texture.h"
#include "Bow.h"
#include "Balloon.h"
#include <vector>
#include <iterator>
#include <list>
#include "Vector2D.h"
#include "checkML.h"
#include "Arrow.h"
#include "ScoreBoard.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "Butterfly.h"

using uint = unsigned int;
using namespace std;

//constantes generales
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 100;
const double PI = 3.14159265;

	//Arco
		const uint VELOCIDAD_ARCO = 5;
		const uint VEL_ROTACION_ARCO = 8;	//velocidad del giro del arco

	//flechas
		const uint FLECHAS_INICIALES = 10;
		const uint VELOCIDAD_FLECHA = 5;
		const uint VELOCIDAD_FLECHA_MAX = 20;
		const uint OFFSET_HITBOX_FLECHA_X = 108;
		const uint OFFSET_HITBOX_FLECHA_Y = 10;

	//globos
		const uint VELOCIDAD_GLOBO = 3;
		const uint LIMITE_IZQUIERDO_GLOBOS = 300;
		const uint LIMITE_DERECHO_GLOBOS = 750;
		const uint VELOCIDAD_ANIMACION_PINCHADO = 5;
		const uint PUNTUACION_POR_GLOBO = 10;
		const double PROBABILIDAD_GLOBO = 20;

	//mariposas
		const uint PUNTOS_POR_MARIPOSA = -5;
		const double VELOCIDAD_MARIPOSA_X = 1;
		const double VELOCIDAD_MARIPOSA_Y = 0.5;
		const uint LIMITE_IZQUIERDO_MARIPOSAS = 100;
		const uint LIMITE_DERECHO_MARIPOSAS = 700;
		const uint LIMITE_ARRIBA_MARIPOSAS = 0;
		const uint LIMITE_ABAJO_MARIPOSAS = 530;
		const uint VELOCIDAD_ANIMACION_MARIPOSAS = 7;
		const uint FRAMES_MUERTA = 50;
		const uint NUMERO_MARIPOSAS = 10;

//UI
const uint SEPARACION_FLECHAS_UI = 15;
const uint SEPARACION_DIGITOS_UI = 30;
const uint TAMAÑO_HITBOX_X = 20;
const uint TAMAÑO_HITBOX_Y = 5;


//Texturas
const uint NUM_TEXTURES = 8;
const uint ESCALA_ARCO = 3;
const uint ESCALA_FLECHA = 3;
const uint ESCALA_GLOBO = 40;
const uint ESCALA_MARIPOSA = 7;

const enum OBJETOS
{
	arrowPhysics, arrowUI, balloons, background1, bowCharged, bowUncharged, digits, butterflys,
};

struct InfoTexture
{
	string direccion;
	int columnas, filas;
};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];
	int numMariposas;
	list<GameObject*> objetos;
	list<Arrow*> flechasObjetos;
	list<list<Arrow*>::iterator> flechasPenDestruccion;
	list<EventHandler*> hEventsObjetos;
	list<list<GameObject*>::iterator> objPenDestruccion;



	GameObject* arco;
	int puntuacion, numFlechas;
	ScoreBoard* scoreBoard;
	vector<InfoTexture> texturesInfo = {
	InfoTexture{"..\\images\\Arrow1.png", 1, 1},
	InfoTexture{"..\\images\\Arrow2.png", 1, 1},
	InfoTexture{"..\\images\\balloons.png", 7, 6},
	InfoTexture{"..\\images\\bg1.png", 1, 1},
	InfoTexture{"..\\images\\Bow1.png", 1, 1},
	InfoTexture{"..\\images\\Bow2.png", 1, 1},
	InfoTexture{"..\\images\\digits1.png", 1, 10},
	InfoTexture{"..\\images\\butterfly2.png", 4, 10}
	};

public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	void disparar(Arrow* r);
	bool colision(SDL_Rect* globoC);
	void actualizaPuntuacion(int puntos);
	void condicionFinDeJuego();
	int returnPuntuacion();
	int returnNumFlechas();
	Texture* returnPuntTextura(int indice);
	void generaGlobo();
	void generaMariposas(int num);
	void mataMariposa();
	void killObject(list<GameObject*>::iterator it);
	void killObjectFlecha(list<Arrow*>::iterator it);
};
