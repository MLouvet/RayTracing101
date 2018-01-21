#pragma once
#include "object.h"
#include "material.h"

class Quad :
	public Object
{
public:
	virtual Hit intersect(const Ray &ray);
	virtual Color colorAt(Point p);

	~Quad();

	Vector N;
	Vector edge1;
	Vector edge2;
	Vector edge3;
	Vector edge4;
	Point point1;
	Point point2;
	Point point3;
	Point point4;
	double d;
	Quad();
	Quad(Point point1, Point point2, Point point3, Point point4) :point1(point1), point2(point2), point3(point3), point4(point4),
		d(-(N.x * point1.x + N.y * point1.y + N.z * point1.z)),
		N(normalFrom4pts( point1,  point2,  point3,  point4)),
		edge1(point2 - point1),
		edge2(point3 - point2),
		edge3(point4 - point3),
		edge4(point1 - point4) {

	}
private :
	Vector normalFrom4pts(Point point1, Point point2, Point point3, Point point4);
	virtual void setRotation(Vector axis, double angle) override;

};

