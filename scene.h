//
//  Framework for a raytracer
//  File: scene.h
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

#ifndef SCENE_H_KNBLQLP6
#define SCENE_H_KNBLQLP6
#define MAX_DEPTH 1

#include <vector>
#include "triple.h"
#include "light.h"
#include "object.h"
#include "image.h"
const double minZ = 550;
const double maxZ = 1000;
class Scene
{
private:
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Triple eye;

public:
	Scene(int renderMode_) : renderMode(RenderMode(renderMode_)) {};
	Color trace(const Ray &ray);
	void render(Image &img);
	void addObject(Object *o);
	void addLight(Light *l);
	void setEye(Triple e);
	unsigned int getNumObjects() { return objects.size(); }
	unsigned int getNumLights() { return lights.size(); }
	enum RenderMode
	{
		Phong = 0, ZBuffer = 1, Normal = 2
	};
	RenderMode renderMode;
	int maxdeph = 2;
};

#endif /* end of include guard: SCENE_H_KNBLQLP6 */
