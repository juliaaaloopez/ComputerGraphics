#pragma once


#include "mesh.h"
#include "image.h"
#include "shader.h"
#include "material.h"


class Entity {

public:

    Mesh* mesh;
    Matrix44 model;
    Material* material;

    Entity() {
        this->mesh = new Mesh;
        this->model = Matrix44(); //Sets identity matrix
        this->material = new Material;

    };

    ~Entity() {};

    //void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer, bool isInterpolated, bool isOcluded, bool isTextured);
    void Render(Material::sUniformData uniformData);
    void Update(float seconds_elapsed, bool rotate, bool translate, bool scale);

};
