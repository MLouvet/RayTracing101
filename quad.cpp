#include "quad.h"



Hit Quad::intersect(const Ray & ray)
{
	Point intersect;

	if (N.dot(ray.D) == 0)
		return Hit::NO_HIT();
	else {
		double t = (-N.dot(ray.O) - d) / (N.dot(ray.D));
		intersect = ray.O + ray.D*t;

		Vector C0 = intersect - point1;
		Vector C1 = intersect - point2;
		Vector C2 = intersect - point3;
		Vector C3 = intersect - point4;
		if (N.dot(edge1.cross(C0)) > 0 &&
			N.dot(edge2.cross(C1)) > 0 &&
			N.dot(edge3.cross(C2)) > 0 &&
			N.dot(edge4.cross(C3)) >0)
			return Hit(t, N.normalized());
	}
	return Hit::NO_HIT();
}

Color Quad::colorAt(Point p)
{
	return material->color;
}

Quad::Quad()
{
}


Vector Quad::normalFrom4pts(Point point1, Point point2, Point point3, Point point4)
{
	Vector v1 = point2 - point1;
	Vector v2 = point2 - point1;

	return v1.cross(v2);
}

Quad::~Quad()
{
}
