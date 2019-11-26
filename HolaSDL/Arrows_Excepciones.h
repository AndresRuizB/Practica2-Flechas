#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"

using namespace std;

class ArrowsError : public logic_error {
public:
	ArrowsError(string& msg) :
		logic_error(msg) {}
};

class SDLError : public ArrowsError {
protected:
	string SDL_Error, IMG_Error;
public:
	SDLError(string& msg) :
		ArrowsError(msg + "Error de SDL: " + SDL_GetError() + " Error de IMG: " + IMG_GetError()),
		SDL_Error(SDL_GetError()), IMG_Error(IMG_GetError()) {}
};

class FileNotFoundError : public ArrowsError {
protected:
	string name;
public : 
	FileNotFoundError(const string& msg, string n) :
		ArrowsError(msg + "Error when opening file " + n) {}
};

class FileFormatError : public ArrowsError {
public:
	FileFormatError(string& m) :
		ArrowsError(m) {}
};