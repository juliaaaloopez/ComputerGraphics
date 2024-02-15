#pragma once


#include "mesh.h"
#include "image.h"

class Entity {

public:

    Mesh* mesh;
    Matrix44 model;
    Image* texture;

    Entity() {
        this->mesh = new Mesh;
        this->model = Matrix44(); //Sets identity matrix
        this->texture = new Image;  //we initialize the texture to a null pointer
    };

    ~Entity() {};

    void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer, bool isInterpolated, bool isOcluded, bool isTextured);
    void Update(float seconds_elapsed, bool rotate, bool translate, bool scale);

};
