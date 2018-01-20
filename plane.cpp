#include "plane.h"

Hit Plane::intersect(const Ray & ray)
{
	//Intersection calculation
	if (N.dot(ray.D) == 0) {
		//No hit possible;
		//cerr << "NO PLANE HIT" << endl;
		return Hit::NO_HIT();
	}
	//Otherwise, find intersection
	//plane equation: ax + by + cz + d = 0
	//parametric equation of the ray:
	//x(t) = ray.D.x * t + ray.O.x
	//y(t) = ray.D.y * t + ray.O.y
	//z(t) = ray.D.z * t + ray.O.z
	//solving ax(t) + by(t) + cz(t) + d = 0

	//As there is an intersection, no need to check for zero-division
	double t = (-N.dot(ray.O) - d) / (N.dot(ray.D));
	return Hit(t, N.normalized());
}

Color Plane::colorAt(Point p)
{
	return material->color;
}

void Plane::setRotation(Vector axis, double angle)
{
	this->rotationAxis = axis; this->angle = angle;
	cerr << "Plane ignores rotation right now" << endl;
}
