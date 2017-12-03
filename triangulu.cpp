#include "triangulu.h"




Hit triangulu::intersect(const Ray & ray)
{
	Point intersect;
	
	if (N().dot(ray.D) == 0) return Hit::NO_HIT();
	else {
		double d = N().x * point1.x + N().y * point1.y + N().z * point1.z;
		double t = (-N().dot(ray.O) - d) / (N().dot(ray.D));
		intersect = ray.O + ray.D*t;
		Vector edge0 = point2 - point1;
		Vector edge1 = point3 - point2;
		Vector edge2 = point1 - point3;
		Vector C0 = intersect - point1;
		Vector C1 = intersect - point2;
		Vector C2 = intersect - point3;
		if (N().dot(edge0.cross(C0)) > 0 &&
			N().dot(edge1.cross(C1)) > 0 &&
			N().dot(edge2.cross(C2)) > 0)
			 return Hit(t, N().normalized());
	}
	return Hit::NO_HIT();
}

triangulu::~triangulu()
{
}

const Vector triangulu::N()
{
	Vector V = Vector(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
	Vector W = Vector(point3.x - point1.x, point3.y - point1.y, point3.z - point1.z);
	return Vector((V.y*W.z)-(V.z*W.y), (V.z*W.x)-(V.x*W.z), (V.x*W.y) - (V.y*W.x));
}
