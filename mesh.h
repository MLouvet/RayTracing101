#pragma once
#include "triangle.h"
#include <vector>
#include <string>

using namespace std;

class Mesh :
	public Object
{
private:
	vector<Triangle> objects;
public:
	virtual Hit intersect(const Ray &ray);
	virtual Color colorAt(Point p);
	Mesh(string path);
	~Mesh();

	// Hérité via Object
	virtual void setRotation(Vector axis, double angle) override;
};

