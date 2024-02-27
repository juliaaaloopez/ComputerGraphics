#pragma once
#include "shader.h"
#include "image.h"
#include "mesh.h"
#include <vector>

class Material {

public:

    Texture* texture_normal;
    Texture* texture_color;
    Shader* shader;
    Vector3 Ka; //ambient reflection
    Vector3 Kd; //reflected diffuse light
    Vector3 Ks; //reflected specular light
    float a; //shininess

    Material() {
        this->shader = new Shader; //we add the shader as an atribute to the entity class
        this->texture_normal = new Texture;
        this->texture_color = new Texture; 
        
    };

    ~Material() {};
    
    void Enable();
    void Disable();
    
    struct sLight {
        Vector2 position;
        Vector3 diffuse_intensity;
        Vector3 specular_intensity;
    };
    
    struct sUniformData{ //only sLight and others, not material
        Matrix44 model;
        Matrix44 viewprojection_matrix;
        Vector3 ambient_light;
        Vector2 position;
        Vector3 diffuse_intensity;
        Vector3 specular_intensity;
    };

};

