#include "mesh.h"
#include "glm.h"
#include "triple.h"
#include "triangle.h"
#include <algorithm>

#include <functional> 
#include <cctype>
#include <locale>

//Credits for trimming functions : https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring?page=1&tab=votes#tab-top
//from Evan Teran

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

Hit Mesh::intersect(const Ray &ray)
{
	return Hit::NO_HIT();
}

Color Mesh::colorAt(Point p)
{
	return Color(128, 128, 128); //Not yet handled
}

Mesh::Mesh(string path, Point offset, float scale)
{
	//Trimming the path

	materialFound = false;
	GLMmodel *model = glmReadOBJ((char *)(path + ".obj").c_str());

	GLMgroup *group = model->groups;
	while (group)
	{
		for (int i = 0; i < group->numtriangles; i++)
		{
			GLMtriangle t = model->triangles[group->triangles[i]];
			Point p1(model->vertices[t.vindices[0] * 3], model->vertices[t.vindices[0] * 3 + 1], model->vertices[t.vindices[0] * 3 + 2]);
			Point p2(model->vertices[t.vindices[1] * 3], model->vertices[t.vindices[1] * 3 + 1], model->vertices[t.vindices[1] * 3 + 2]);
			Point p3(model->vertices[t.vindices[2] * 3], model->vertices[t.vindices[2] * 3 + 1], model->vertices[t.vindices[2] * 3 + 2]);

			p1 += offset;
			p2 += offset;
			p3 += offset;

			p1.rotateAround(rotationAxis, angle);
			p2.rotateAround(rotationAxis, angle);
			p3.rotateAround(rotationAxis, angle);

			Triangle *triangle = new Triangle(p1, p2, p3);

			//Trimming groupnames, as it seems to hhave unwanted spaces
			string groupName = trim( string(group->name));

			int numMaterial = glmFindMaterial(model, (char *)groupName.c_str());
			if (numMaterial)
				materialFound = true;
			GLMmaterial m = model->materials[numMaterial];
			Material *material = new Material();
			material->ka = m.ambient[0];
			material->kd = m.diffuse[0];
			material->ks = m.specular[0];
			material->color = Color(m.diffuse[0], m.diffuse[1], m.diffuse[2]);

			triangle->material = material;
			objects.push_back(triangle);
		}
		group = group->next;
	}

	//Cleaning up
	glmDelete(model);
}

Mesh::~Mesh()
{
}

void Mesh::fiilScene(Scene *s)
{
	for (int i = 0; i < objects.size(); i++)
	{
		s->addObject(objects[i]);
	}
}

void Mesh::setMaterial(Material *m)
{
	if (!materialFound)
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->material = m;
		}
}

void Mesh::setRotation(Vector axis, double angle)
{
	rotationAxis = axis;
	this->angle = angle;
}
