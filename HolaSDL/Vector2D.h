#pragma once
#include <string>
#include "checkML.h"

class Vector2D
{
private:
	double x=0, y=0;
public:

	Vector2D() {};
	Vector2D(double x,double y);
	~Vector2D();

	double GetX()const { return x; };
	double GetY()const { return y; };

	void Normalizar();
	Vector2D operator+(const Vector2D& vector) const;
	Vector2D operator-(const Vector2D& vector) const;
	Vector2D operator*(const Vector2D vector) const;
	void ProductoPorEscalar(double escalar);
};
