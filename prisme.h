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
		t1.material->ka = t2.material->ka = q1.material->ka = q2.material->ka = q3.material->ka = material->ka;
		t1.material->kd = t2.material->kd = q1.material->kd = q2.material->kd = q3.material->kd = material->kd;
		t1.material->ks = t2.material->ks = q1.material->ks = q2.material->ks = q3.material->ks = material->ks;
		t1.material->n = t2.material->n = q1.material->n = q2.material->n = q3.material->n = material->n;
		t1.material->texture = t2.material->texture = q1.material->texture = q2.material->texture = q3.material->texture = material->texture;
		t1.material->color = t2.material->color = q1.material->color = q2.material->color = q3.material->color = material->color;
	}
	~Prisme();
private:
	virtual void setRotation(Vector axis, double angle) override;
};

