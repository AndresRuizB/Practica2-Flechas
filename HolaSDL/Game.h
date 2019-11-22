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

using uint = unsigned int;
using namespace std;

//constantes generales
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 100;
const double PI = 3.14159265;

//constantes de velocidades
const uint VELOCIDAD_ARCO = 5;
const uint VEL_ROTACION_ARCO = 8;	//velocidad del giro del arco
const uint VELOCIDAD_FLECHA = 5;
const uint VELOCIDAD_FLECHA_MAX = 20;
const uint VELOCIDAD_GLOBO = 1;
const uint VELOCIDAD_ANIMACION_PINCHADO = 5;

//constantes de cantidad
const uint PUNTUACION_POR_GLOBO = 10;
const uint FLECHAS_INICIALES = 10;
const double PROBABILIDAD_GLOBO = 35;

//constantes de medidas
const uint LIMITE_IZQUIERDO_GLOBOS = 300;
const uint LIMITE_DERECHO_GLOBOS = 750;
const uint SEPARACION_FLECHAS_UI = 15;
const uint SEPARACION_DIGITOS_UI = 30;
const uint TAMAÑO_HITBOX_X = 20;
const uint TAMAÑO_HITBOX_Y = 5;
const uint OFFSET_HITBOX_FLECHA_X = 108;
const uint OFFSET_HITBOX_FLECHA_Y = 10;

//escalas Texturas
const uint ESCALA_ARCO = 3;
const uint ESCALA_FLECHA = 3;
const uint ESCALA_GLOBO = 40;

const enum OBJETOS
{
	arrowPhysics, arrowUI, balloons, background1, bowCharged, bowUncharged, digits,
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

	list<GameObject*> objetos;
	list<Arrow*> flechasObjetos;
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
	void actualizaPuntuacion();
	void condicionFinDeJuego();
	int returnPuntuacion();
	int returnNumFlechas();
	Texture* returnPuntTextura(int indice);
	void generaGlobo();
	void killObject(list<GameObject*>::iterator it);
};
