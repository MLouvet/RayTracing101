#include "triangle.h"




Hit Triangle::intersect(const Ray & ray)
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
		if (N.dot(edge0.cross(C0)) > 0 &&
			N.dot(edge1.cross(C1)) > 0 &&
			N.dot(edge2.cross(C2)) > 0)
			 return Hit(t, N.normalized());
	}
	return Hit::NO_HIT();
}

Triangle::~Triangle()
{
}

Vector Triangle::normalFrom3Points(Point p1, Point p2, Point p3)
{
	Vector V = Vector(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	Vector W = Vector(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
	return Vector((V.y*W.z) - (V.z*W.y), (V.z*W.x) - (V.x*W.z), (V.x*W.y) - (V.y*W.x));
}