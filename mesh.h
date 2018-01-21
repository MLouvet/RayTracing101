#pragma once
#include "Triangle.h"
#include "scene.h"
#include <vector>
#include <string>

using namespace std;

class Mesh :
	public Object
{
private:
	bool materialFound;
public:
	vector<Triangle*> objects;
	vector<Image*> textures;
	Image* getTexture(int index);
	vector<int> textureIndexes;
	virtual Hit intersect(const Ray &ray);
	virtual Color colorAt(Point p);
	Mesh(string path, Point offset, float scale);
	~Mesh();
	void fiilScene(Scene* s);

	// H�rit� via Object
	virtual void setRotation(Vector axis, double angle) override;
	void Mesh::setMaterial(Material*m);
};

