#include "Arrow.h"
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"
#include <list>

Arrow::Arrow(Texture* t, Game* g)
{
	game = g;
	ancho = t->getW();
	alto = t->getH();
	textura = t;
	posicion = Vector2D(0, 0);
	velocidad = 0;
	angulo = 0;
}

Arrow::~Arrow()
{
}

void Arrow::render() {
	SDL_Rect frameDestino;
	frameDestino.w = ancho / ESCALA_FLECHA;
	frameDestino.h = alto / ESCALA_FLECHA;
	frameDestino.x = posicion.GetX();
	frameDestino.y = posicion.GetY();

	textura->renderFrame(frameDestino, 0, 0, angulo, SDL_FLIP_NONE);	//renderframe para poder rotarla
}

//establece la velocidad inicial de la flecha
void Arrow::estableceVel(int vel) {
	velocidad = vel;
}

//establece la posicion de la flecha
void Arrow::establecePos(Vector2D pos) {
	posicion = Vector2D(pos.GetX(), 55 + pos.GetY());
}

//establece el anulo de la flecha
void Arrow::estableceAng(double ang) {
	angulo = ang;
}

//mueve la flecha (true si sigue en la pantalla)
void Arrow::update() {
	posicion = posicion + Vector2D(velocidad * cos(angulo * PI / 180), velocidad * (sin(angulo * PI / 180))); //cambia la posicion dependiendo del angulo
	if (posicion.GetX() > WIN_WIDTH || posicion.GetX() < 0 || posicion.GetY() > WIN_HEIGHT || posicion.GetY() < 0) {
		game->killObject(posicionEnEstructura);
		game->killObjectFlecha(posEnEstrFlechas);
	}

}

SDL_Rect Arrow::getDestRect() { return SDL_Rect(); }

SDL_Rect Arrow::getCollisionRect() {
	SDL_Rect p;
	p.w = TAMAÑO_HITBOX_X;
	p.h = TAMAÑO_HITBOX_Y; //dimensiones de la hitbox
	p.x = posicion.GetX() + OFFSET_HITBOX_FLECHA_X;
	p.y = posicion.GetY() + OFFSET_HITBOX_FLECHA_Y; //calcula la posicion de la punta
	return p;
}

void Arrow::loadFromFile() {}

void Arrow::saveToFile() {}

void Arrow::setItList(list<GameObject*>::iterator it) { posicionEnEstructura = it; }

void Arrow::setItListFlechas(list<Arrow*>::iterator it) { posEnEstrFlechas = it; }

