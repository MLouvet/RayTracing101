//
//  Framework for a raytracer
//  File: sphere.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//
//  This framework is inspired by and uses code of the raytracer framework of 
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html 
//

#include "sphere.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Sphere::intersect(const Ray &ray)
{
	/****************************************************
	* RT1.1: INTERSECTION CALCULATION
	*
	* Given: ray, position, r
	* Sought: intersects? if true: *t
	*
	* Insert calculation of ray/sphere intersection here.
	*
	* You have the sphere's center (C) and radius (r) as well as
	* the ray's origin (ray.O) and direction (ray.D).
	*
	* If the ray does not intersect the sphere, return Hit::NO_HIT().
	* Otherwise, return an instance of Hit() with the distance of the
	* intersection point from the ray origin as t and the normal ad N (see example).
	****************************************************/


	//parametric equation of the ray:
	//x(t) = ray.D.x * t + ray.O.x
	//y(t) = ray.D.y * t + ray.O.y
	//z(t) = ray.D.z * t + ray.O.z
	//sphere : (x - position.x)² + (y - position.y)² + (z - position.z)² = r²
	//solving : (ray.D.x - position.x)² + (rayy - position.y)² + (z - position.z)² = r²

	Point intersection;
	//Calculating the discriminant
	double a, b, c, d, t, ox, oy, oz; //ox.y.z just used for calculus
	ox = ray.O.x - position.x;
	oy = ray.O.y - position.y;
	oz = ray.O.z - position.z;

	a = ray.D.x*ray.D.x + ray.D.y*ray.D.y + ray.D.z*ray.D.z;
	b = 2 * (ray.D.x * ox + ray.D.y * oy + ray.D.z * oz);
	c = ox*ox + oy*oy + oz*oz - r*r;
	d = b*b - 4 * a*c;

	if (d < 0.0) {
		return Hit::NO_HIT();
	}
	else if (d == 0.0) {
		//One hit, at the edge of the sphere for t = -b/2a
		t = -b / (2 * a);
	}
	else {
		double t1, t2, x1, x2, y1, y2, z1, z2, l1, l2;
		Point p1, p2;
		//Two hits, at t = (-b - sqrt(d))/2a and (-b + sqrt(d))/2a
		//Determining minimum distance between source of ray and collision
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);

		x1 = ray.D.x * t1 + ray.O.x;
		y1 = ray.D.y * t1 + ray.O.y;
		z1 = ray.D.z * t1 + ray.O.z;
		x2 = ray.D.x * t2 + ray.O.x;
		y2 = ray.D.y * t2 + ray.O.y;
		z2 = ray.D.z * t2 + ray.O.z;

		//Comparing square of lengths to get the nearest
		l1 = (x1 - ray.O.x) * (x1 - ray.O.x) + (y1 - ray.O.y) * (y1 - ray.O.y) + (z1 - ray.O.z) * (z1 - ray.O.z);
		l2 = (x2 - ray.O.x) * (x2 - ray.O.x) + (y2 - ray.O.y) * (y2 - ray.O.y) + (z2 - ray.O.z) * (z2 - ray.O.z);
		t = l1 < l2 ? t1 : t2;
	}

	intersection = Point::Triple(ray.D.x * t + ray.O.x, ray.D.y * t + ray.O.y, ray.D.z * t + ray.O.z);


	/****************************************************
	* RT1.2: NORMAL CALCULATION
	*
	* Given: t, C, r
	* Sought: N
	*
	* Insert calculation of the sphere's normal at the intersection point.
	****************************************************/

	Vector N = (intersection - position);

	return Hit(t, N);
}
