#pragma once
#include "object.h"
#include "material.h"
class Triangle :
	public Object
{
public:
	virtual Hit intersect(const Ray &ray);
	virtual Color colorAt(Point p);

	~Triangle();
	Vector N;
	Vector edge1;
	Vector edge2;
	Vector edge3;
	Point point1;
	Point point2;
	Point point3;
	double d;


	Triangle(Point point1, Point point2, Point point3) : point1(point1), point2(point2), point3(point3),
		N(normalFrom3Points(point1, point2, point3)),
		d(-(N.x * point1.x + N.y * point1.y + N.z * point1.z)),
		edge1(point2 - point1),
		edge2(point3 - point2),
		edge3(point1 - point3)
	{}

private:
	Vector normalFrom3Points(Point p1, Point p2, Point p3);


	// Hérité via Object
	virtual void setRotation(Vector axis, double angle) override;

};

