#pragma once


#include "mesh.h"
#include "image.h"
#include "shader.h"
#include "material.h"


class Entity {

public:

    Mesh* mesh;
    Matrix44 model;
    Texture* texture;
    Shader* shader;

    Entity() {
        this->mesh = new Mesh;
        this->model = Matrix44(); //Sets identity matrix
        this->texture = new Texture;  //we initialize the texture to a null pointer
        this->shader = new Shader; //we add the shader as an atribute to the entity class
        
    };

    ~Entity() {};

    //void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer, bool isInterpolated, bool isOcluded, bool isTextured);
    void Render(sUniformData uniformData);
    void Update(float seconds_elapsed, bool rotate, bool translate, bool scale);

};
