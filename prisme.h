#pragma once
#include "object.h"
#include "material.h"
#include "triangle.h"
#include "quad.h"

class Prisme :
	public Object
{
public:
	virtual Hit intersect(const Ray &ray);
	virtual Color colorAt(Point p);
	Triangle t1, t2;
	Quad q1, q2, q3;
	Prisme(Triangle t1, Triangle t2, Quad q1, Quad q2, Quad q3) : t1(t1), t2(t2), q1(q1), q2(q2), q3(q3) {
	}
	~Prisme();
private:
	//virtual void setMaterial(Material *m) override;
	virtual void setRotation(Vector axis, double angle) override;
};

