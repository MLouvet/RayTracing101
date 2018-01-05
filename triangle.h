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
	const Vector N;
	const Vector edge0;
	const Vector edge1;
	const Vector edge2;
	const Point point1;
	const Point point2;
	const Point point3;
	const double d;
	const double thickness;


	Triangle(Point point1, Point point2, Point point3, double thickness) : point1(point1), point2(point2), point3(point3), thickness(thickness),
		N(normalFrom3Points(point1, point2, point3)),
		d(N.x * point1.x + N.y * point1.y + N.z * point1.z),
		edge0(point2 - point1),
		edge1(point3 - point2),
		edge2(point1 - point3)
	{}
private:
	Vector normalFrom3Points(Point p1, Point p2, Point p3);

};

