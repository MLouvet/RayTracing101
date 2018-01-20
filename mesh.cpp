#include "mesh.h"
#include "glm.h"
#include "triple.h"
#include "triangle.h"



Hit Mesh::intersect(const Ray & ray)
{
	return Hit::NO_HIT();
}

Color Mesh::colorAt(Point p)
{
	return Color(128, 128, 128);	//Not yet handled
}

Mesh::Mesh(string path, Point offset, float scale)
{
	GLMmodel* model = glmReadOBJ((char *)(path + ".obj").c_str());

	//GLMgroup* group = model->groups;
	//while (group) {
	//	for (int i = 0; i < group->numtriangles; i++)
	//	{
	//		GLMtriangle t = model->triangles[group->triangles[i]];
	//		Point p1(model->vertices[t.vindices[0] * 3], model->vertices[t.vindices[0] * 3 + 1], model->vertices[t.vindices[0] * 3 + 2]);
	//		Point p2(model->vertices[t.vindices[1] * 3], model->vertices[t.vindices[1] * 3 + 1], model->vertices[t.vindices[1] * 3 + 2]);
	//		Point p3(model->vertices[t.vindices[2] * 3], model->vertices[t.vindices[2] * 3 + 1], model->vertices[t.vindices[2] * 3 + 2]);


	//		p1 += offset;
	//		p2 += offset;
	//		p3 += offset;
	//		cout << p1 << endl;
	//		cout << p2 << endl;
	//		cout << p3 << endl;

	//		//p1.rotateAround(rotationAxis, angle);
	//		//p2.rotateAround(rotationAxis, angle);
	//		//p3.rotateAround(rotationAxis, angle);

	//		Triangle *triangle = new Triangle(p1, p2, p3);

	//		GLMmaterial m = model->materials[glmFindMaterial(model, group->name)];
	//		Material *material = new Material();
	//		material->ka = *m.ambient;
	//		material->kd = *m.diffuse;
	//		material->ks = *m.specular;

	//		triangle->material = material;
	//		objects.push_back(triangle);
	//	}
	//	group = group->next;
	//}
		for (int i = 0; i < model->numtriangles; i++)
		{
			GLMtriangle t = model->triangles[i];
			Point p1(model->vertices[t.vindices[0] * 3], model->vertices[t.vindices[0] * 3 + 1], model->vertices[t.vindices[0] * 3 + 2]);
			Point p2(model->vertices[t.vindices[1] * 3], model->vertices[t.vindices[1] * 3 + 1], model->vertices[t.vindices[1] * 3 + 2]);
			Point p3(model->vertices[t.vindices[2] * 3], model->vertices[t.vindices[2] * 3 + 1], model->vertices[t.vindices[2] * 3 + 2]);


			p1 += offset;
			p2 += offset;
			p3 += offset;
			cout << p1 << endl;
			cout << p2 << endl;
			cout << p3 << endl;

			//p1.rotateAround(rotationAxis, angle);
			//p2.rotateAround(rotationAxis, angle);
			//p3.rotateAround(rotationAxis, angle);

			Triangle *triangle = new Triangle(p1, p2, p3);

			//GLMmaterial m = model->materials[glmFindMaterial(model, group->name)];
			//Material *material = new Material();
			//material->ka = *m.ambient;
			//material->kd = *m.diffuse;
			//material->ks = *m.specular;

			//triangle->material = material;
			objects.push_back(triangle);
		}
	//Cleaning up
	glmDelete(model);
}

Mesh::~Mesh()
{
}

void Mesh::fiilScene(Scene * s)
{
	for (int i = 0; i < objects.size(); i++)
	{
		s->addObject(objects[i]);
	}
}

void Mesh::setMaterial(Material* m) {
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
