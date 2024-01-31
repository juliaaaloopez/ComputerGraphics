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
    
    Entity(Mesh* my_mesh, Vector3 trans, Vector3 rotate, Vector3 scale, float angle){
        model.SetIdentity();
        model.Translate(trans.x, trans.y, trans.y);
        model.Rotate(angle*DEG2RAD, rotate);
        Matrix44 m_scale;
        m_scale.M[0][0] = scale.x;
        m_scale.M[1][1] = scale.y;
        m_scale.M[2][2] = scale.z;
        model = m_scale * model;
        
    };
    
    ~Entity() {};

    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void Update(float seconds_elapsed, bool rotate, bool translate, bool scale);


};
