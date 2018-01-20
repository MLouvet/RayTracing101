//
//  Framework for a raytracer
//  File: object.h
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

#ifndef OBJECT_H_AXKLE0OF
#define OBJECT_H_AXKLE0OF

#include "triple.h"
#include "light.h"

class Material;

class Object {
protected:
	Triple rotationAxis;
	double angle;
public:
    Material *material;
	Object() : material(NULL), angle(.0) {}
	virtual ~Object() { }
	virtual Color colorAt(Point p) = 0;
	virtual void setRotation(Vector axis, double angle) = 0;	//Might imply transformation on the child object
    virtual Hit intersect(const Ray &ray) = 0;
	virtual void setMaterial(Material* m) { material = m; }
};

#endif /* end of include guard: OBJECT_H_AXKLE0OF */
