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
	Vector edge0;
	Vector edge1;
	Vector edge2;
	Point point1;
	Point point2;
	Point point3;
	double d;
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


	// Hérité via Object
	virtual void setRotation(Vector axis, double angle) override;

};

