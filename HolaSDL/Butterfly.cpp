#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Butterfly.h"
#include "Texture.h"
#include "Game.h"
#include <list>

using namespace std;

Butterfly::Butterfly(Texture* t, Game* g)
{
	game = g;
	int x = rand() % (LIMITE_DERECHO_MARIPOSAS - LIMITE_IZQUIERDO_MARIPOSAS) + LIMITE_IZQUIERDO_MARIPOSAS;
	int y = rand() % (LIMITE_ABAJO_MARIPOSAS - LIMITE_ARRIBA_MARIPOSAS) + LIMITE_ARRIBA_MARIPOSAS;
	posicion = Vector2D(x, y);
	int velY = rand() % 3, velX = rand() % 3 + 1;
	direccion = Vector2D(velX * VELOCIDAD_MARIPOSA_X, velY * VELOCIDAD_MARIPOSA_Y);
	ancho = t->getW();
	alto = t->getH();
	textura = t;
	frameDestino = SDL_Rect{};
	tiempoMuerta = 0;
	muerta = false;
	frame = 0;
}

Butterfly::~Butterfly()
{ //destructora
}

void Butterfly::update() {	//devuelve true si el globo sigue vivo

	if (!muerta) {
		posicion = posicion + direccion; //calcula la proxima posicion segun su direccion

		if (posicion.GetY() > LIMITE_ABAJO_MARIPOSAS || posicion.GetY() < LIMITE_ARRIBA_MARIPOSAS) {
			direccion = Vector2D(1, -1) * direccion + Vector2D(rand() % 2 - 1.0, 0);
		}

		if (posicion.GetX() > LIMITE_DERECHO_MARIPOSAS || posicion.GetX() < LIMITE_IZQUIERDO_MARIPOSAS) {
			direccion = Vector2D(-1, 1) * direccion + Vector2D(0, rand() % 2 - 1.0);
		}
	}
	else posicion = posicion + Vector2D(0, 1);

	frameDestino.w = ancho / ESCALA_MARIPOSA; //su tamaño proporcional
	frameDestino.h = alto / ESCALA_MARIPOSA; //estos dos valores nunca cambian
	frameDestino.x = posicion.GetX();
	frameDestino.y = posicion.GetY();

	//COLISION
	if (game->colision(&frameDestino)) {
		muerta = true;
	}

	if (tiempoMuerta > FRAMES_MUERTA) {
		game->actualizaPuntuacion(PUNTOS_POR_MARIPOSA);
		game->killObject(posicionEnEstructura);
		game->mataMariposa();
	}

}


void Butterfly::render() {
	textura->renderFrame(frameDestino, 0, (frame / VELOCIDAD_ANIMACION_MARIPOSAS) % 4, 0, SDL_FLIP_NONE);
	if (muerta)	tiempoMuerta++;
	else frame++;
}

double Butterfly::returnY() {
	return posicion.GetY(); //devuelve su posicion y
}

SDL_Rect Butterfly::getDestRect() { return SDL_Rect(); }
SDL_Rect Butterfly::getCollisionRect() { return SDL_Rect(); }
void Butterfly::loadFromFile() {}
void Butterfly::saveToFile(ofstream* output) {
	*output << "\nbutterfly\n";
	*output << "posicion " << posicion.GetX() << " " << posicion.GetY() << "\n";
	*output << "direccion " << direccion.GetX() << " " << direccion.GetY() << "\n";
	*output << "frame " << frame << "\n";
	*output << "timepoMuerta " << tiempoMuerta << "\n";
	*output << "muerta " << muerta << "\n";
}

void Butterfly::setItList(list<GameObject*>::iterator it) { posicionEnEstructura = it; }