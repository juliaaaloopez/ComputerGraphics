#pragma once


#include "mesh.h"
#include "image.h"

class Entity {

public:

	Mesh* mesh;
	Matrix44 model;

	Entity() {};
	~Entity() {};

	void Render(Image* framebuffer, Camera* camera, const Color& c);

	void Update(float seconds_elapsed);


};