#pragma once
#include "triple.h"
class Camera
{
public:
	Camera() {};
	Camera(Triple eye_, Triple center_, Triple up_, int width_, int height_) : eye(eye_), center(center_), up(up_), width(width_), height(height_) {};
	Triple eye;
	Triple center;
	Triple up;
	int width, height;
};

