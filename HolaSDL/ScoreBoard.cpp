#include "ScoreBoard.h"
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "Game.h"

ScoreBoard::ScoreBoard(Texture* tDigitos, Texture* tFlechas)
{
	numFlechas = 0;
	texturaDigitos = tDigitos;
	texturaFlechas = tFlechas;
	posicionDigitos = Vector2D(120, 0);
	ancho = texturaDigitos->getW() / 10;//al ancho de cada frame
	alto = texturaDigitos->getH();
	puntuacion = 0;
}

ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::render() {
	SDL_Rect frameDestino;
	frameDestino.w = ancho/2;
	frameDestino.h = alto/2;
	frameDestino.x = posicionDigitos.GetX();
	frameDestino.y = posicionDigitos.GetY();

	int punt = puntuacion; //copia de puntuacion por que se tiene que ir dividiendo entre 10
	if(punt==0)texturaDigitos->renderFrame(frameDestino, 0, (punt % 10), 0, SDL_FLIP_NONE); //en el cado de tener 0 puntos
	while (punt > 0) {
		texturaDigitos->renderFrame(frameDestino, 0, (punt % 10), 0, SDL_FLIP_NONE); //renderiza cada digito
		frameDestino.x -= SEPARACION_DIGITOS_UI;
		punt /= 10; 
	} //renderiza la puntuacion

	frameDestino.w = ancho / 7;
	frameDestino.h = alto / 2;
	frameDestino.x = 160;
	frameDestino.y = 0;
	for (int i = 0; i < numFlechas; i++) {
		texturaFlechas->renderFrame(frameDestino, 0, (punt % 10), 0, SDL_FLIP_NONE);
		frameDestino.x += SEPARACION_FLECHAS_UI;
	} //renderiza el numero de flechas restantes
}

void ScoreBoard::actualizaPuntuacion(int punt) {
	puntuacion = punt;
}

void ScoreBoard::actualizaFlechas(int numF) {
	numFlechas = numF;
}