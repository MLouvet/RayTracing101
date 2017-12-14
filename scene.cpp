//
//  Framework for a raytracer
//  File: scene.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//	  Mathieu Louvet
//    Bryan Vigée
//
//  This framework is inspired by and uses code of the raytracer framework of 
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html 
//

#include <algorithm>
#include "scene.h"
#include "material.h"


Color Scene::trace(const Ray &ray)
{
	// Find hit object and distance
	Hit min_hit(std::numeric_limits<double>::infinity(), Vector());
	Hit max_hit(std::numeric_limits<double>::infinity(), Vector());
	Object *obj = NULL;
	for (unsigned int i = 0; i < objects.size(); ++i) {
		Hit hit(objects[i]->intersect(ray));
		if (hit.t < min_hit.t) {
			min_hit = hit;
			obj = objects[i];
		}
	}

	// No hit? Return background color.
	if (!obj) return Color(0.0, 0.0, 0.0);

	Material *material = obj->material;            //the hit objects material
	Point hit = ray.at(min_hit.t);                 //the hit point
	Vector N = min_hit.N;                          //the normal at hit point
	Vector V = -ray.D;                             //the view vector


	//cout << whiteValue << endl;
	switch (renderMode)
	{
		case Scene::Phong:
		{
			/****************************************************
			* This is where you should insert the color
			* calculation (Phong model).
			*
			* Given: material, hit, N, V, lights[]
			* Sought: color
			*
			* Hints: (see triple.h)
			*        Triple.dot(Vector) dot product
			*        Vector+Vector      vector sum
			*        Vector-Vector      vector difference
			*        Point-Point        yields vector
			*        Vector.normalize() normalizes vector, returns length
			*        double*Color        scales each color component (r,g,b)
			*        Color*Color        dito
			*        pow(a,b)           a to the power of b
			****************************************************/
			// place holder
			Color cAmbiant, cDiffuse, cSpecular, cReflected;
			bool shadow = false;
			for (unsigned int i = 0; i < lights.size(); i++) {
				shadow = false;
				Light* l = lights[i];
				Vector vL = (l->position - hit);
				double lightDistance = vL.length();
				vL.normalize();
				Vector R = (2.0 * (vL.dot(N)) * N - vL).normalized();/*
				for each (Object* o in objects)
				{
					if (o == obj) continue;
					Hit h = o->intersect(Ray(hit, vL, ray.depth));
					if (!h.no_hit) {
						if (h.t < lightDistance) {
							shadow = true;
							break;
						}
					}
				}*/

				//Calculation of ambient light: ka * La
				cAmbiant += material->ka * material->color * l->color;

				//Calculation of diffuse reflection: kd * Ld * L.N
				if (!shadow)
					cDiffuse += material->kd * material->color * l->color * max(vL.dot(N), 0.0);

				//Calculation of specular light: ks * Ls * (v.r)^alpha with r: reflection of v of 180° around N
				if (!shadow)
					cSpecular += material->ks * l->color *  pow(max(0.0, V.dot(R)), material->n);
			}

			//Calculation of reflection
			//Vector R = (2.0 * (N.dot(V)) * N - V).normalized();
			//if (ray.depth > 0) {
			//	cReflected += material->ks * trace(Ray(hit, R, ray.depth - 1));

			//}
			return cAmbiant + cDiffuse + cSpecular + cReflected;
			break;
		}
		case Scene::ZBuffer:	// percent of interval : maxZ-minZ
		{
			Color whiteC;
			whiteC.set((minZ - min_hit.t) / (maxZ - minZ));
			return whiteC;
		}
		case Scene::Normal:
			return Color((N + 1) / 2);
		case Scene::Flat:
			return material->color;
		default:
			cerr << "Render mode not implemented";
			return Color(0, 0, 0);
			break;
	}


}

void Scene::render(Image &img)
{
	int w = img.width();
	int h = img.height();
	double pointOffset = 1.0 / aaLevel;
	double pixelBorderOffset = 0.5 * pointOffset;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			maxdepth = MAX_DEPTH;
			Color col;
			double aaOffset = pixelBorderOffset;
			for (int i = 0; i < aaLevel; i++)
			{
				for (int j = 0; j < aaLevel; j++)
				{
					Point pixel((double)x + pixelBorderOffset + (double)i * pointOffset, (double)h - 1.0 - (double)y + pixelBorderOffset + (double)j * pointOffset, 0);
					Ray ray(eye, (pixel - eye).normalized(), maxdepth);
					col = col + trace(ray);
				}
			}
			col /= pow(aaLevel,2);
			col.clamp();
			img(x, y) = col;
		}
	}
}

void Scene::addObject(Object *o)
{
	objects.push_back(o);
}

void Scene::addLight(Light *l)
{
	lights.push_back(l);
}

void Scene::setEye(Triple e)
{
	eye = e;
}
