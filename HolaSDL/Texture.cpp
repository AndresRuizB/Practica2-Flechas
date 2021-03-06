#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"

#include "Texture.h"
#include <iostream>
#include "Arrows_Excepciones.h"

using namespace std;

void Texture::libre() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw FileNotFoundError("Error al cargar la superficie ", filename) ;
	libre();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw FileNotFoundError("Error al cargar la textura ", filename);
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

//renderiza la textura entera
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}


//renderiza un frame concreto dado
void Texture::renderFrame(const SDL_Rect& frameDestino, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;

	SDL_RenderCopyEx(renderer, texture, &srcRect, &frameDestino, angle, 0, flip);
}