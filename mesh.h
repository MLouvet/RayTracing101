#pragma once
#include "triangle.h"
#include "scene.h"
#include <vector>
#include <string>

using namespace std;

class Mesh :
	public Object
{
public:
	vector<Triangle*> objects;
	virtual Hit intersect(const Ray &ray);
	virtual Color colorAt(Point p);
	Mesh(string path, Point offset, float scale);
	~Mesh();
	void fiilScene(Scene* s);

	// Hérité via Object
	virtual void setRotation(Vector axis, double angle) override;
	void Mesh::setMaterial(Material*m);
	};

