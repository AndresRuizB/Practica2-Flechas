#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

class ScoreBoard
{
private:
	Vector2D posicionDigitos; //posicion del primer dígito
	Texture* texturaDigitos;
	Texture* texturaFlechas;
	int ancho, alto, puntuacion, numFlechas;
public:
	ScoreBoard(Texture*tDigitos, Texture* tFlechas);
	~ScoreBoard();
	void render();
	void actualizaPuntuacion(int punt);
	void actualizaFlechas(int numF);
};