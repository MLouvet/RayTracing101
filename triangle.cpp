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
	//if (material->texture == NULL)
		return material->color;
	//else {
	//	Vector v0 = point2 - point1;
	//	Vector v1 = point3 - point1;
	//	Vector v2 = p - point1;
	//	float d00 = v0.dot(v0);
	//	float d01 = v0.dot(v1);
	//	float d11 = v1.dot(v1);
	//	float d20 = v2.dot(v0);
	//	float d21 = v2.dot(v1);
	//	float denom = d00 * d11 - d01 * d01;
	//	double v = (d11 * d20 - d01 * d21) / denom;
	//	double w = (d00 * d21 - d01 * d20) / denom;
	//	double u = 1.0f - v - w;
	//}
	//return material->texture->colorAt(xTex, yTex);
}

Triangle::~Triangle()
{
}


void Triangle::setTextureWithCoordinates(Image* tex, int x, int y)
{
	if (material == NULL)
		return;
	material->texture = tex;
	xTex = x;
	yTex = y;
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
