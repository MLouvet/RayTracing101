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
	double a, b, c, d, t;
	Point distance = ray.O - position;

	a = ray.D.length_2();
	b = 2 * ray.D.dot(distance);
	c = distance.length_2() - pow(r, 2);
	d = pow(b, 2) - 4 * a * c;

	if (d < 0.0) {
		return Hit::NO_HIT();
	}
	else if (d == 0.0) {
		//One hit, at the edge of the sphere for t = -b/2a
		t = -b / (2 * a);
	}
	else {
		double t1, t2;
		//Two hits, at t = (-b - sqrt(d))/2a and (-b + sqrt(d))/2a
		//Determining minimum distance between source of ray and collision
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);

		t = t1 < t2 ? t1 : t2;
	}



	/****************************************************
	* RT1.2: NORMAL CALCULATION
	*
	* Given: t, C, r
	* Sought: N
	*
	* Insert calculation of the sphere's normal at the intersection point.
	****************************************************/

	intersection = ray.D * t + ray.O;
	Vector N = intersection - position;
	return Hit(t, N.normalized());
}
