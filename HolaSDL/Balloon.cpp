#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Balloon.h"
#include "Texture.h"
#include "Game.h"
#include <list>
#include "Arrows_Excepciones.h"
#include <fstream>
#include "Game.h"
#include "App.h"

using namespace std;

Balloon::Balloon(Texture* t, Game* g)
{
	game = g;
	int x = rand() % (LIMITE_DERECHO_GLOBOS - LIMITE_IZQUIERDO_GLOBOS) + LIMITE_IZQUIERDO_GLOBOS; //crea un numero entre 400-750
	posicion = Vector2D(x, 600); //pone la poscion del globo
	int velY = rand() % 5; //numero entre 0 y 5
	direccion = Vector2D(0, (((double)(VELOCIDAD_GLOBO)+((double)velY - 2)) * -1)); //la velocidad del globo es base al cual se le suma o resta un numero entre [-2,2]
	ancho = t->getW();
	alto = t->getH();
	textura = t;
	globo = rand() % 6;
	frameDestino = SDL_Rect{};
	globosPinchadosTemp = 0, globosPinchados = 0;

	pinchado = false;
	momentoPinchado = 0; //0 cuando no ha sido pinchado
}

Balloon::~Balloon()
{ //destructora
}

void Balloon::update() {	//devuelve true si el globo sigue vivo

	if (!pinchado) posicion = posicion + direccion; //calcula la proxima posicion segun su direccion

	frameDestino.w = ancho / ESCALA_GLOBO; //su tamaño proporcional
	frameDestino.h = alto / ESCALA_GLOBO; //estos dos valores nunca cambian
	frameDestino.x = posicion.GetX();
	frameDestino.y = posicion.GetY();

	//COLISION
	if (!pinchado && game->colision(&frameDestino, globosPinchadosTemp)) {
		pinchado = true;
		globosPinchados = globosPinchadosTemp;
	}

	if (momentoPinchado > (VELOCIDAD_ANIMACION_PINCHADO * 5)) {
		game->actualizaPuntuacion(pow(globosPinchados-1,2) * PUNTUACION_POR_GLOBO + PUNTUACION_POR_GLOBO);
		game->killObject(posicionEnEstructura);
		game->createReward(posicion.GetX(), posicion.GetY());
	}
	else if (posicion.GetY() + (alto / ESCALA_GLOBO) <= 0) { //si se ha salido o ha terminado la animacion de destruirse
		game->killObject(posicionEnEstructura);
	}
}


void Balloon::render() {
	if (pinchado)
	{
		textura->renderFrame(frameDestino, globo, (momentoPinchado / VELOCIDAD_ANIMACION_PINCHADO) + 1, 0, SDL_FLIP_NONE); // +1 para evitar el primer frame que es el globo solo 
		momentoPinchado++; //tiempo transcurrido desde el momento en el que se ha pinchado
	}
	else {
		textura->renderFrame(frameDestino, globo, 0, 0, SDL_FLIP_NONE); //se carga al render el normal
	}
}

double Balloon::returnY() {
	return posicion.GetY(); //devuelve su posicion y
}

SDL_Rect Balloon::getDestRect() { return SDL_Rect(); }
SDL_Rect Balloon::getCollisionRect() { return SDL_Rect(); }


void Balloon::loadFromFile(ifstream* input) {
	int x, y;
	*input >> x;
	*input >> y;
	posicion = Vector2D(x, y);
	*input >> x;
	*input >> y;
	direccion = Vector2D(x, y);
	*input >> pinchado;
	*input >> momentoPinchado;
	*input >> globo;
	*input >> globosPinchados;
}

void Balloon::saveToFile(ofstream* output) {
	*output << "\nbaloon\n";
	*output << posicion.GetX() << " " << posicion.GetY() << "\n";
	*output << direccion.GetX() << " " << direccion.GetY() << "\n";
	*output << pinchado << "\n";
	*output << momentoPinchado << "\n";
	*output << globo << "\n";
	*output << globosPinchados << "\n"; //globosPinchadosTemp empieza siempre en 0
}

void Balloon::setItList(list<GameObject*>::iterator it) { posicionEnEstructura = it; }