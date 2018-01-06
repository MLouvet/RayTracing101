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
#include "image.h"

class Material;

class Object {
protected:
	double theta, phi; //Rotation coordinates
public:
    Material *material;
	Image *texture;
	Object() : texture(NULL), material(NULL), theta(.0), phi(.0) {}
	virtual ~Object() { }
	virtual Color colorAt(Point p) = 0;
	virtual void setPolarRotation(double theta, double phi) = 0;	//Might imply transformation on the child object
    virtual Hit intersect(const Ray &ray) = 0;
};

#endif /* end of include guard: OBJECT_H_AXKLE0OF */
