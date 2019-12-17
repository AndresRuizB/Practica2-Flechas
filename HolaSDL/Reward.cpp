#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Reward.h"
#include "Texture.h"
#include "Vector2D.h"

#include "Arrows_Excepciones.h"
#include <fstream>
#include "App.h"
#include "Game.h"



Reward::Reward(Texture* t, Game* g, Texture* b, int x, int y)
{
	textura = t;
	game = g;
	burbuja = b;
	posicion = Vector2D(x, y);
	direccion = Vector2D(0, VELOCIDAD_CAIDA_REWARD);
	frameDestino = SDL_Rect{};
	tipo_reward = rand() % NUMERO_DE_REWARDS;
	estado_rotacion = 0;
	ancho = t->getW();
	alto = t->getH();
	conBurbuja = true;
	frameDestinoBurbuja = SDL_Rect();
}

Reward::~Reward()
{
}


void Reward::render() {
	if (conBurbuja) {
		textura->renderFrame(frameDestino, tipo_reward, (estado_rotacion/VELOCIDAD_ROTACION_REWARD)%8, 0, SDL_FLIP_NONE);
		burbuja->render(frameDestinoBurbuja, SDL_FLIP_NONE);
	}
	else textura->renderFrame(frameDestino, tipo_reward, (estado_rotacion / VELOCIDAD_ROTACION_REWARD) % 8, 0, SDL_FLIP_NONE);

	estado_rotacion++;
}

void Reward::update() {
	posicion = posicion + direccion;

	frameDestino.w = ancho / ESCALA_REWARD; //su tama�o proporcional
	frameDestino.h = alto / ESCALA_REWARD; //estos dos valores nunca cambian
	frameDestino.x = posicion.GetX();
	frameDestino.y = posicion.GetY();

	frameDestinoBurbuja = frameDestino;
	frameDestinoBurbuja.w = ancho / ESCALA_BURBUJA;
	frameDestinoBurbuja.h = alto / ESCALA_BURBUJA;
	frameDestinoBurbuja.x += OFFSET_SPAWN_REWARD_X;
	frameDestinoBurbuja.y += OFFSET_SPAWN_REWARD_Y;  //VALORES MAGICOS

	if (game->colision(&frameDestinoBurbuja))conBurbuja = false;

	if (posicion.GetY() > WIN_HEIGHT) {
		game->killObject(posicionEnEstructura);
		game->killObjectEventHandler(posicionEnEventos);
	}

}



SDL_Rect Reward::getDestRect() {
	return SDL_Rect();
}
SDL_Rect Reward::getCollisionRect() {
	return SDL_Rect();
}
void Reward::loadFromFile(ifstream* input) {
	int x, y;
	*input >> x;
	*input >> y;
	posicion = Vector2D(x, y);
	*input >> x;
	*input >> y;
	direccion = Vector2D(x, y);
	*input >> tipo_reward;
	*input >> estado_rotacion;
	*input >> conBurbuja;

}

void Reward::saveToFile(ofstream* output) {
	*output << "\nreward\n";
	*output << posicion.GetX() << " " << posicion.GetY() << "\n";
	*output << direccion.GetX() << " " << direccion.GetY() << "\n";
	*output << tipo_reward << "\n";
	*output << estado_rotacion << "\n";
	*output << conBurbuja << "\n";
}


void Reward::setItList(list<GameObject*>::iterator it) {
	posicionEnEstructura = it;
}

void Reward::setItListEventHandler(list<EventHandler*>::iterator it) {
	posicionEnEventos = it;
}

void Reward::handleEvent(SDL_Event& event) {
	if (!conBurbuja && event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		SDL_Point punto;

		punto.x = x;
		punto.y = y;
		if (SDL_PointInRect(&punto,&frameDestinoBurbuja)) {
			if (tipo_reward == 0) game->sumaFlechas();
			else if (tipo_reward == 1) game->pasoNivelReward();
			else if (tipo_reward == 2) game->crearButterflyReward();
			else if (tipo_reward == 3) game->creaGlobosReward();
			game->killObject(posicionEnEstructura);
			game->killObjectEventHandler(posicionEnEventos);
		}
	}
}