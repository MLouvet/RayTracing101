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
		if (N.dot(edge1.cross(C0)) > 0 &&
			N.dot(edge2.cross(C1)) > 0 &&
			N.dot(edge3.cross(C2)) > 0)
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
	Vector V = p2 - p1;
	return V.cross(p3 - p1);
}

void Triangle::setRotation(Vector axis, double angle)
{
	this->rotationAxis = axis; this->angle = angle;
	
	Point centroid = (point1 + point2 + point3) / 3;
	
	point1 = point1.rotateAround(axis, angle);
	point2 = point2.rotateAround(axis, angle);
	point3 = point3.rotateAround(axis, angle);

	//Recalculating every coordinate after rotation
	N = normalFrom3Points(point1, point2, point3);
	d = N.x * point1.x + N.y * point1.y + N.z * point1.z;
	edge1 = point2 - point1;
	edge2 = point3 - point2;
	edge3 = point1 - point3;
}
