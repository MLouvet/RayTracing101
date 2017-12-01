#pragma once
#include "object.h"
class Plane :
	public Object
{
public:
	Plane(Vector normal, double d) : N(normal), d(d) {};
	virtual Hit intersect(const Ray &ray);
	const Vector N;
	const double d;
};

