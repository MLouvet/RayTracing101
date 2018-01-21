#include "prisme.h"



Hit Prisme::intersect(const Ray & ray)
{
	Hit th1 = t1.intersect(ray), th2 = t2.intersect(ray), qh1 = q1.intersect(ray), qh2 = q2.intersect(ray), qh3 = q3.intersect(ray);
	double ret = 10000;
	Hit retu = Hit::NO_HIT();
	if (!th1.no_hit)
	{
		ret = th1.t; retu = th1;
	}
	if (!th2.no_hit && (ret < th2.t || ret == 10000)) {
		ret = th2.t; retu = th2;
	}
	if (!qh1.no_hit && (ret < qh1.t || ret == 10000)) {
		ret = qh1.t; retu = qh1;
	}
	if (!qh2.no_hit && (ret < qh2.t || ret == 10000)) {
		ret = qh2.t; retu = qh2;
	}
	if (!qh3.no_hit && (ret < qh3.t || ret == 10000)) {
		ret = qh3.t; retu = qh3;
	}
	return retu;
}

Color Prisme::colorAt(Point p)
{
	return material->color;
}


Prisme::~Prisme()
{
}

//void Prisme::setMaterial(Material * m)
//{
//	this->material = t1.material = t2.material = q1.material = q2.material = q3.material = m;
//}

void Prisme::setRotation(Vector axis, double angle)
{
}
