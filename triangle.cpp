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

Color Triangle::colorAt(Point p)
{
	return material->color;
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

void Triangle::setPolarRotation(double theta, double phi)
{
	this->theta = theta; this->phi = phi;
	
	Point centroid = (point1 + point2 + point3) / 3;
	
	//Recalculating every coordinate after rotation
	point1 = point1.rotateAround(centroid, theta, phi);
	point2 = point2.rotateAround(centroid, theta, phi);
	point3 = point3.rotateAround(centroid, theta, phi);

	N = normalFrom3Points(point1, point2, point3);
	d = N.x * point1.x + N.y * point1.y + N.z * point1.z;
	edge0 = point2 - point1;
	edge1 = point3 - point2;
	edge2 = point1 - point3;
}
