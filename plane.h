#pragma once
#include "object.h"
#include "material.h"
class Plane :
	public Object
{
public:
	Plane(Vector normal, double d) : N(normal), d(d) {};
	virtual Hit intersect(const Ray &ray);
	const Vector N;
	const double d;
	virtual Color colorAt(Point p);

	// Hérité via Object
	virtual void setRotation(Vector axis, double angle) override;
};

