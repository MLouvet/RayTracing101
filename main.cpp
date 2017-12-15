//
//  Framework for a raytracer
//  File: main.cpp
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

#include "raytracer.h"
#ifdef WIN32
#include "windows.h"
#endif
int outputError();
int main(int argc, char *argv[])
{
	Raytracer raytracer;
	string ofname = "";
	Scene::RenderMode renderMode = Scene::RenderMode::None;
	int aaLevel = -1;

	cout << "Introduction to Computer Graphics - Raytracer" << endl << endl;



	//Reading parameters
	if (argc < 2 || argc % 2 == 1) {	// Small preview check
		cerr << "Parameter missing or left alone." << endl;
		return outputError();
	}
	try
	{
		for (int i = 2; i + 1 < argc; i += 2)
		{
			string optType = argv[i], optValue = argv[i + 1];
			if (optType == "-o") {
				if (ofname != "") {	//Output file check
					cerr << "Output file already selected. Exiting" << endl;
					return 2;
				}
				ofname = optValue;
			}
			else if (optType == "-r") { //Render mode check
				if (renderMode != Scene::RenderMode::None) {
					cerr << "Illumination mode already selected. Exiting" << endl;
					return 2;
				}
				if (optValue == "phong")
					renderMode = Scene::RenderMode::Phong;
				if (optValue == "z-buffer")
					renderMode = Scene::RenderMode::ZBuffer;
				if (optValue == "normal")
					renderMode = Scene::RenderMode::Normal;
				if (optValue == "flat")
					renderMode = Scene::RenderMode::Flat;

				else {
					cerr << "Unknown illumination mode. Exiting" << endl;
					return 2;
				}
			}
			else if (optType == "-a") {//Antialiasing check
				if (aaLevel != -1) {
					cerr << "Anti-aliasing level already selected. Exiting" << endl;
					return 2;
				}
				if (stoi(optValue) < 1) {
					cerr << "Invalid anti-aliasing level selected. Exiting" << endl;
					return 2;
				}
				else aaLevel = stoi(optValue);
			}
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what();
		outputError();
	}
	if (renderMode == Scene::RenderMode::None)
		renderMode = Scene::RenderMode::Phong;
	if (aaLevel == -1)
		aaLevel = 1;

	//Generating scene

	if (!raytracer.readScene(argv[1], renderMode, aaLevel)) {
		cerr << "Error: reading scene from " << argv[1] << " failed - no output generated." << endl;
		return 1;
	}
	else if (ofname == "") {
		ofname = argv[1];
		if (ofname.size() >= 5 && ofname.substr(ofname.size() - 5) == ".yaml") {
			ofname = ofname.substr(0, ofname.size() - 5);
		}
		ofname += ".png";
	}
	raytracer.renderToFile(ofname);
#ifdef WIN32
	ShellExecute(0, 0, ofname.c_str(), 0, 0, SW_SHOW);
#endif
	return 0;
}

int outputError() {
	cerr << "Usage: " << "RayTracer in-file.yaml" << endl;
	cerr << "Options available:" << endl
		<< "\t-o output_file.png to specify output file" << endl
		<< "\t-r for render: phong (default) / z-buffer / normal / flat" << endl
		<< "\t-a for antialiasing level: 1 (default), 2, 3, any strictly positive integer. Might result in long render time for large values";
	return 1;
}
