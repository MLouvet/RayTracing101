//
//  Framework for a raytracer
//  File: raytracer.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Author: Maarten Everts
//
//  This framework is inspired by and uses code of the raytracer framework of 
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html 
//

#include "raytracer.h"
#include "plane.h"
#include "object.h"
#include "sphere.h"
#include "material.h"
#include "triangle.h"
#include "light.h"
#include "image.h"
#include "yaml/yaml.h"
#include <ctype.h>
#include <fstream>
#include <assert.h>

// Functions to ease reading from YAML input
void operator >> (const YAML::Node& node, Triple& t);
Triple parseTriple(const YAML::Node& node);

void operator >> (const YAML::Node& node, Triple& t)
{
	assert(node.size() == 3);
	node[0] >> t.x;
	node[1] >> t.y;
	node[2] >> t.z;
}

Triple parseTriple(const YAML::Node& node)
{
	Triple t;
	node[0] >> t.x;
	node[1] >> t.y;
	node[2] >> t.z;
	return t;
}

Material* Raytracer::parseMaterial(const YAML::Node& node)
{
	Material *m = new Material();
	// Loading a potential texture
	if (node.FindValue("texture") != 0) {
		string s = node["texture"];
		m->texture = new Image(s.c_str());
	}
	else {
		m->texture = NULL;
		node["color"] >> m->color;
	}
	node["ka"] >> m->ka;
	node["kd"] >> m->kd;
	node["ks"] >> m->ks;
	node["n"] >> m->n;
	return m;
}

Camera Raytracer::parseCamera(const YAML::Node & node)
{
	Camera c;
	c.eye = parseTriple(node["eye"]);
	c.center = parseTriple(node["center"]);
	c.up = parseTriple(node["up"]);
	c.width = node["viewSize"][0];
	c.height = node["viewSize"][1];
	return c;
}


Scene::RenderMode Raytracer::parseRenderMode(const YAML::Node & node)
{
	string optValue = node;
	if (optValue == "phong")
		return Scene::RenderMode::Phong;
	if (optValue == "z-buffer")
		return Scene::RenderMode::ZBuffer;
	if (optValue == "normal")
		return Scene::RenderMode::Normal;
	if (optValue == "flat")
		return Scene::RenderMode::Flat;
	else
		throw new exception("Unknown illumination mode.");
}

Object* Raytracer::parseObject(const YAML::Node& node)
{
	Object *returnObject = NULL;
	std::string objectType;
	node["type"] >> objectType;

	if (objectType == "sphere") {
		Point pos;
		node["position"] >> pos;
		double r;
		node["radius"] >> r;
		Sphere *sphere = new Sphere(pos, r);
		returnObject = sphere;
	}
	else if (objectType == "plane") {
		Vector normal;
		node["normal"] >> normal;
		double d;
		node["d"] >> d;
		Plane *plane = new Plane(normal, d);
		returnObject = plane;
	}
	else if (objectType == "triangle") {
		double thick;
		Point p1, p2, p3;
		node["point1"] >> p1;
		node["point2"] >> p2;
		node["point3"] >> p3;
		node["e"] >> thick;
		returnObject = new Triangle(p1, p2, p3, thick);
	}

	if (returnObject) {
		//Loading a potential rotation
		if (node.FindValue("rotation") != 0) {
			try
			{
				returnObject->setPolarRotation(node["rotation"][0], node["rotation"][1]);
			}
			catch (const std::exception&) { cerr << "Expected rotation parameters like this [theta, phi]. Rotation ignored" << endl; }
		}

		// read the material and attach to object
		returnObject->material = parseMaterial(node["material"]);
	}

	return returnObject;
}

Light* Raytracer::parseLight(const YAML::Node& node)
{
	Point position;
	node["position"] >> position;
	Color color;
	node["color"] >> color;
	return new Light(position, color);
}


/*
* Read a scene from file
*/

bool Raytracer::readScene(const std::string& inputFilename)
{
	// Initialize a new scene
	scene = new Scene();

	// Open file stream for reading and have the YAML module parse it
	std::ifstream fin(inputFilename.c_str());
	if (!fin) {
		cerr << "Error: unable to open " << inputFilename << " for reading." << endl;;
		return false;
	}
	try {
		YAML::Parser parser(fin);
		if (parser) {
			YAML::Node doc;
			parser.GetNextDocument(doc);

			// Read scene configuration options
			try
			{
				scene->setEye(parseTriple(doc["Eye"]));
			}
			catch (const std::exception&) {
				//No eye, trying to find a camera object
				scene->setCamera(parseCamera(doc["Camera"]));
			}

			//These following parameters are not mandatory, hence, only a try is needed.
			try {
				scene->setRenderShadows(doc["Shadows"]);
			}
			catch (const std::exception&) {}
			try {
				scene->setMaxDepth(doc["MaxRecursionDepth"]);
			}
			catch (const std::exception&) {}
			try {
				scene->setSuperSampling(doc["SuperSampling"]["factor"]);
			}
			catch (const std::exception&) {}
			try
			{
				scene->setRenderMode(parseRenderMode(doc["Render"]));
			}
			catch (const std::exception&) {}




			// Read and parse the scene objects
			const YAML::Node& sceneObjects = doc["Objects"];
			if (sceneObjects.GetType() != YAML::CT_SEQUENCE) {
				cerr << "Error: expected a sequence of objects." << endl;
				return false;
			}
			for (YAML::Iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
				Object *obj = parseObject(*it);
				// Only add object if it is recognized
				if (obj) {
					scene->addObject(obj);
				}
				else {
					cerr << "Warning: found object of unknown type, ignored." << endl;
				}
			}

			// Read and parse light definitions
			const YAML::Node& sceneLights = doc["Lights"];
			if (sceneObjects.GetType() != YAML::CT_SEQUENCE) {
				cerr << "Error: expected a sequence of lights." << endl;
				return false;
			}
			for (YAML::Iterator it = sceneLights.begin(); it != sceneLights.end(); ++it) {
				scene->addLight(parseLight(*it));
			}
		}
		if (parser) {
			cerr << "Warning: unexpected YAML document, ignored." << endl;
		}
	}
	catch (YAML::ParserException& e) {
		std::cerr << "Error at line " << e.mark.line + 1 << ", col " << e.mark.column + 1 << ": " << e.msg << std::endl;
		return false;
	}

	cout << "YAML parsing results: " << scene->getNumObjects() << " objects read." << endl;
	return true;
}

void Raytracer::renderToFile(const std::string& outputFilename)
{
	Image img(scene->getSceneWidth(), scene->getSceneHeight());
	cout << "Tracing..." << endl;
	scene->render(img);
	cout << "Writing image to " << outputFilename << "..." << endl;
	img.write_png(outputFilename.c_str());
	cout << "Done." << endl;
}
