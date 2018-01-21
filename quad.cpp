#include "quad.h"
#include "triangle.h"


Hit Quad::intersect(const Ray & ray)
{
	Triangle t1(point1, point2,point3), t2(point1, point2, point4)
		, t3(point1, point4, point3), t4(point4, point2, point3);
	Hit h1 = t1.intersect(ray), h2=t2.intersect(ray), h3=t3.intersect(ray), h4=t4.intersect(ray);
	if (!h1.no_hit || !h2.no_hit || !h3.no_hit || !h4.no_hit)
	{
		double t = (-N.dot(ray.O) - d) / (N.dot(ray.D));
		if (!h1.no_hit && h1.t > t)
			t = h1.t;
		if (!h2.no_hit && h2.t > t)
			t = h2.t;
		if (!h3.no_hit && h3.t > t)
			t = h3.t;
		if (!h4.no_hit && h4.t > t)
			t = h4.t;
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
	Triangle t1(point1, point2, point3), t2(point1, point2, point4)
		, t3(point1, point4, point3), t4(point4, point2, point3);
	return t1.N+t2.N+t3.N+t4.N;
}

void Quad::setRotation(Vector axis, double angle)
{
}

Quad::~Quad()
{
}
