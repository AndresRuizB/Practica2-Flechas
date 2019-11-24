#include <iostream>
#include "checkML.h"
#include <string>

#include "Vector2D.h"

Vector2D::Vector2D(double _X, double _Y) {
	x = _X;
	y = _Y;
}

Vector2D::~Vector2D() {

}

//normaliza un vector
void Vector2D::Normalizar() {
	double modulo = sqrt((x * x) + (y * y));
	x /= modulo;
	y /= modulo;
} //normaliza este vector

//suma dos vectores
Vector2D Vector2D::operator+(const Vector2D& vector) const {
	Vector2D r;
	r.x = this->x + vector.GetX();
	r.y = this->y + vector.GetY();
	return r;
}

//resta dos vectores
Vector2D Vector2D::operator-(const Vector2D& vector) const {
	Vector2D r;
	r.x = x - vector.x;
	r.y = y - vector.y;
	return r;
}

Vector2D Vector2D::operator*(const Vector2D vector) const {
	Vector2D producto;
	producto.x = (x * vector.x);
	producto.y = (y * vector.y);
	return producto;
} //devuelve el producto de dos vectores

void Vector2D::ProductoPorEscalar(double escalar) {
	x *= escalar;
	y *= escalar;
} //escala este vector por un numero dado