#pragma once


#include "mesh.h"
#include "image.h"

class Entity {

public:

    Mesh* mesh;
    Matrix44 model;

    Entity() {
        this->mesh = new Mesh;
        this->model = Matrix44(); //Sets identity matrix
    };

    ~Entity() {};

    void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer);
    void Update(float seconds_elapsed, bool rotate, bool translate, bool scale);

    /*enum class eRenderMode {
        POINTCLOUD,
        WIREFRAME,
        TRIANGLES,
        TRIANGLES_INTERPOLATED
    };
    eRenderMode mode;*/

};
