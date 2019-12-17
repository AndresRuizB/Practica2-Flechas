#pragma once


#include "Texture.h"
#include <vector>
#include <iterator>
#include <list>
#include "Vector2D.h"
#include "checkML.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "GameStateMachine.h"


using uint = unsigned int;
using namespace std;

//constantes generales
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 100;
const double PI = 3.14159265;
const uint NUMERO_NIVELES = 6;
const uint NIVEL_INICIAL = 0;
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
const uint VELOCIDAD_GLOBO = 2;
const uint LIMITE_IZQUIERDO_GLOBOS = 300;
const uint LIMITE_DERECHO_GLOBOS = 750;
const uint VELOCIDAD_ANIMACION_PINCHADO = 5;
const uint PUNTUACION_POR_GLOBO = 10;
const double PROBABILIDAD_GLOBO = 30;

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

//Rewards
const uint VELOCIDAD_CAIDA_REWARD = 1;
const uint VELOCIDAD_ROTACION_REWARD = 7;
const uint PROBABILIDAD_REWARD = 30;  //en porcentaje
const uint SUMA_FLECHAS = 3;
const uint OFFSET_SPAWN_REWARD_X = -17;
const uint OFFSET_SPAWN_REWARD_Y = -12;
const uint NUMERO_DE_REWARDS = 4;
const uint CANTIDAD_MAX_GLOBOS_REWARD = 12;
const uint CANTIDAD_MIN_GLOBOS_REWARD = 6;	// No puede ser mayor ni igual que el maximo

//UI
const uint SEPARACION_FLECHAS_UI = 15;
const uint SEPARACION_DIGITOS_UI = 30;
const uint TAMANO_HITBOX_X = 20;
const uint TAMANO_HITBOX_Y = 5;

//Texturas

const uint NUM_TEXTURES = 18;
const uint ESCALA_ARCO = 3;
const uint ESCALA_FLECHA = 3;
const uint ESCALA_GLOBO = 40;
const uint ESCALA_MARIPOSA = 7;
const uint ESCALA_REWARD = 7;
const uint ESCALA_BURBUJA = 4;

const enum OBJETOS
{
	arrowPhysics, arrowUI, balloons, bowCharged, bowUncharged, digits, butterflys, background0, background1, background2, background3, background4, background5, reward, burbuja, playbutton, exitbutton, loadbutton,
};

struct InfoTexture
{
	string direccion;
	int columnas, filas;
};

struct InfoLevels
{
	int numero;
	int puntosSigNivel;
	int nMariposas;
	int flechasAlLlegar;
};

const vector<InfoTexture> texturesInfo = {
	InfoTexture{"..\\images\\Arrow1.png", 1, 1},
	InfoTexture{"..\\images\\Arrow2.png", 1, 1},
	InfoTexture{"..\\images\\balloons.png", 7, 6},
	InfoTexture{"..\\images\\Bow1.png", 1, 1},
	InfoTexture{"..\\images\\Bow2.png", 1, 1},
	InfoTexture{"..\\images\\digits1.png", 1, 10},
	InfoTexture{"..\\images\\butterfly2.png", 4, 10},
	InfoTexture{"..\\images\\bg_spring_trees_1.png", 1, 1},
	InfoTexture{"..\\images\\bg1.png", 1, 1},
	InfoTexture{"..\\images\\Cartoon_Forest_BG_01.png", 1, 1},
	InfoTexture{"..\\images\\Cartoon_Forest_BG_03.png", 1, 1},
	InfoTexture{"..\\images\\Cartoon_Forest_BG_02.png", 1, 1},
	InfoTexture{"..\\images\\Cartoon_Forest_BG_04.png", 1, 1},
	InfoTexture{"..\\images\\rewards.png",10,8},
	InfoTexture{"..\\images\\bubble.png",1,1},
	InfoTexture{"..\\images\\play.png",1,1},
	InfoTexture{"..\\images\\exit.png",1,1},
	InfoTexture{"..\\images\\load.png",1,1},
};


enum Boton { play, save, menu, exitt, load };

class App {
private:
	vector<InfoLevels> levelsInfo = {
		InfoLevels{0, 300, 4, 0},
		InfoLevels{1, 100, 6, 1},
		InfoLevels{2, 250, 7, 2},
		InfoLevels{3, 600, 4, 3},
		InfoLevels{4, 1300, 3, 4},
		InfoLevels{5, 99999, 1, 20},
	};

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Texture* textures[NUM_TEXTURES];
	GameStateMachine* maquinaEstados;

	bool exit = false;

public:
	App();
	~App();

	void run();
	Texture* returnTexture(OBJETOS obj);
	void pushStateApp(GameState* gState);
	void popStateApp();
};