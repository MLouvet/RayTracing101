#include "mesh.h"
#include "glm.h"
#include "triple.h"
#include "triangle.h"



Hit Mesh::intersect(const Ray & ray)
{
	for (int i = 0; i < objects.size(); i++)
	{
		Hit h = objects[i].intersect(ray);
		if (!h.no_hit)
			return h;
	}
	return Hit::NO_HIT();
}

Color Mesh::colorAt(Point p)
{
	return Color(128, 128, 128);	//Not yet handled
}

Mesh::Mesh(string path)
{
	GLMmodel* model = glmReadOBJ((char *)(path + ".obj").c_str());

	GLMgroup* group = model->groups;
	while (group) {
		for (int i = 0; i < group->numtriangles; i++)
		{
			GLMtriangle t = model->triangles[group->triangles[i]];
			Point p1(model->vertices[t.vindices[0] * 3], model->vertices[t.vindices[0] * 3 + 1], model->vertices[t.vindices[0] * 3 + 2]);
			Point p2(model->vertices[t.vindices[1] * 3], model->vertices[t.vindices[1] * 3 + 1], model->vertices[t.vindices[1] * 3 + 2]);
			Point p3(model->vertices[t.vindices[2] * 3], model->vertices[t.vindices[2] * 3 + 1], model->vertices[t.vindices[2] * 3 + 2]);

			p1.rotateAround(rotationAxis, angle);
			p2.rotateAround(rotationAxis, angle);
			p3.rotateAround(rotationAxis, angle);

			Triangle triangle(p1, p2, p3, 0);

			GLMmaterial m = model->materials[glmFindMaterial(model, group->name)];
			Material *material = new Material();
			material->ka = *m.ambient;
			material->kd = *m.diffuse;
			material->ks = *m.specular;

			triangle.material = material;
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

void Mesh::setRotation(Vector axis, double angle)
{
	rotationAxis = axis;
	this->angle = angle;
}
