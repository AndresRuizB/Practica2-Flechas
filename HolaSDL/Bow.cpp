#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Bow.h"
#include "Arrow.h"
#include "Game.h"
#include <list>
#include "Arrows_Excepciones.h"
#include <fstream>

using namespace std;


Bow::Bow(Texture* t, Game* g) {
	textura = t;
	ancho = t->getW();
	alto = t->getH();
	posicion = Vector2D(50, 100);
	direccion = Vector2D(0, 0);
	game = g;
	cargado = false;
	flecha = nullptr;
	velFlecha = VELOCIDAD_FLECHA; //inicializa la velocidad
	angulo = 0;
}

Bow::~Bow()
{
}

//avisa a su textura q se rendere
void Bow::render() { //tiene que llanar al renderer de su textura
	SDL_Rect frameDestino;
	frameDestino.w = ancho / ESCALA_ARCO;
	frameDestino.h = alto / ESCALA_ARCO;
	frameDestino.x = posicion.GetX();
	frameDestino.y = posicion.GetY();

	textura->renderFrame(frameDestino, 0, 0, angulo, SDL_FLIP_NONE);	//renderframe para poder rotarlo
};

void Bow::update() {
	if (posicion.GetY() + direccion.GetY() > 0 && posicion.GetY() + direccion.GetY() < 450)posicion = posicion + direccion;
	if (cargado && velFlecha < VELOCIDAD_FLECHA_MAX)velFlecha += 0.1f; //si esta cargado la velocidad acumulado va subiendo hasta el maximo
}


void Bow::handleEvent(SDL_Event& event) {
	direccion = Vector2D(0, 0); //se hace de esta manera para evitar aceleracion
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			direccion = direccion - Vector2D(0, VELOCIDAD_ARCO);	//arriba
			break;
		case SDLK_DOWN:
			direccion = direccion + Vector2D(0, VELOCIDAD_ARCO);	//abajo
			break;
		case SDLK_o:
			angulo += VEL_ROTACION_ARCO;	//rotar hacia arriba
			break;
		case SDLK_l:
			angulo -= VEL_ROTACION_ARCO;	//rotar hacia abajo
			break;

		case SDLK_LEFT: //carga una flecha
			if (game->returnNumFlechas() > 0) { //si quedan flechas en el "cargador"
				cambioTextura(game->returnPuntTextura(bowCharged)); //pasa al frame cargado del arco
				cargado = true;
			}
			break;
		case SDLK_RIGHT: //dispara
			disparar();
			break;
		}
	}
}

void Bow::cambioTextura(Texture* t) {	//cambia la textura del arco y actualiza los datos
	textura = t;
	ancho = t->getW();
	alto = t->getH(); //actualiza los datos de la textura
}

void Bow::disparar() {
	if (cargado) { //si esta cargado
		Arrow* r = new Arrow(game->returnPuntTextura(arrowPhysics),game);
		flecha = r; //asigna la flecha
		flecha->estableceVel(velFlecha);
		flecha->establecePos(posicion); //actualiza las variables de la flecha
		flecha->estableceAng(angulo);	//iguala el angulo de la flecha al del arco
		game->disparar(flecha); //avisa al gama que se dispara
		cargado = false;
		cambioTextura(game->returnPuntTextura(bowUncharged)); //pasa al frame descargado del arco
		velFlecha = VELOCIDAD_FLECHA;
	}
}

SDL_Rect Bow::getDestRect() { return SDL_Rect(); }
SDL_Rect Bow::getCollisionRect() { return SDL_Rect(); }

void Bow::loadFromFile(ifstream* input) {
	int x, y;
	*input >> x;
	*input >> y;
	posicion = Vector2D(x, y);
	*input >> x;
	*input >> y;
	direccion = Vector2D(x, y);
	*input >> cargado;
	*input >> angulo;
	*input >> velFlecha;
	if (cargado) cambioTextura(game->returnPuntTextura(bowCharged));
}

void Bow::saveToFile(ofstream* output) {	
	*output << "\nbow\n";
	*output << posicion.GetX() << " " << posicion.GetY() << "\n";
	*output << direccion.GetX() << " " << direccion.GetY() << "\n";
	*output << cargado << "\n";
	*output << angulo << "\n";
	*output << velFlecha << "\n";
}

void Bow::setItList(list<GameObject*>::iterator it) { posicionEnEstructura = it; }