#include "mesh.h"
#include "glm.h"
#include "triple.h"
#include "triangle.h"
#include <algorithm>
#include <fstream>

bool fexists(const char *filename)
{
	ifstream file(filename, ios::in);

	if (file)
	{
		file.close();
		return true;
	}
	return false;
}

Image * Mesh::getTexture(int index)
{
	for (int i = 0; i < textureIndexes.size(); i++)
	{
		if (textureIndexes[i] == index)
			return textures[i];
	}
	return nullptr;
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
	materialFound = false;
	GLMmodel *model = glmReadOBJ((char *)(path + ".obj").c_str());


	//Reading textures
	for (int i = 0; i < model->nummaterials; i++)
	{
		GLMmaterial m = model->materials[i];
		if (fexists(m.name)) //Corresponds to texture
		{
			textureIndexes.push_back(i);
			textures.push_back(new Image(m.name));
		}
	}



	GLMgroup *group = model->groups;
	while (group)
	{
		for (int i = 0; i < group->numtriangles; i++)
		{
			GLMtriangle t = model->triangles[group->triangles[i]];
			Point p1(model->vertices[t.vindices[0] * 3], model->vertices[t.vindices[0] * 3 + 1], model->vertices[t.vindices[0] * 3 + 2]);
			Point p2(model->vertices[t.vindices[1] * 3], model->vertices[t.vindices[1] * 3 + 1], model->vertices[t.vindices[1] * 3 + 2]);
			Point p3(model->vertices[t.vindices[2] * 3], model->vertices[t.vindices[2] * 3 + 1], model->vertices[t.vindices[2] * 3 + 2]);

			p1 *= scale;
			p2 *= scale;
			p3 *= scale;

			p1 += offset;
			p2 += offset;
			p3 += offset;

			p1.rotateAround(rotationAxis, angle);
			p2.rotateAround(rotationAxis, angle);
			p3.rotateAround(rotationAxis, angle);

			Triangle *triangle = new Triangle(p1, p2, p3);

			if (group->material >= 0 && group->material < model->nummaterials) {
				GLMmaterial m = model->materials[group->material];



				Material *material = new Material();
				material->ka = m.ambient[0];
				material->kd = m.diffuse[0];
				material->ks = m.specular[0];
				material->color = Color(m.diffuse[0], m.diffuse[1], m.diffuse[2]);

				triangle->material = material;


				materialFound = true;

				//DOESNT WORK
				/*Image* texture = this->getTexture(group->material);
				if (texture) {
					triangle->setTextureWithCoordinates(texture, model->texcoords[t.tindices[0] * 3], model->texcoords[t.tindices[0] * 3 + 1]);
				}
				else {
					triangle->material->texture = NULL;
				}*/
			}
			else
				cout << "Erreur de .png" << endl;

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
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->setRotation(axis, angle);
	}
	rotationAxis = axis;
	this->angle = angle;
}
