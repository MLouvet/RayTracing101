#pragma once
#include "object.h"
class triangulu :
	public Object
{
public:
	triangulu(Point point1, Point point2, Point point3, double thickness): point1(point1), point2(point2), point3(point3), thickness(thickness){}
	
	virtual Hit intersect(const Ray &ray);

	~triangulu();
	const Vector N();
	const Point point1;
	const Point point2;
	const Point point3;
	const double thickness;
};

