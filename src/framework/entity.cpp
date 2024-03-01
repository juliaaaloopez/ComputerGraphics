#include "entity.h"

void Entity::Render(Material::sUniformData uniformData){
    
    uniformData.model = model;
    material->Enable(uniformData);
    mesh->Render(GL_TRIANGLES);
    material->Disable();
}


void Entity::Update(float seconds_elapsed, bool rotate, bool translate, bool scale) {

    if (rotate) {
        float angular_speed = 1.0f; // choose a speed in radians/second
        Vector3 r(0.0f, 1.0f, 0.0f); // rotate around the y-axis
        model.Rotate(angular_speed * seconds_elapsed, r);

    }
    else if (translate) {
        float translation_speed = 0.5f; // choose a speed in units/second
        float translation_distance = translation_speed * seconds_elapsed; //it will translate this distance over time

        Vector3 t(translation_distance, 0.0f, 0.0f); // translate in the x-axis
        model.Translate(t.x, t.y, t.z);


    }
    else if (scale) {
        float scaleSpeed = 0.2f;  //chosen speed of the scalation
        Vector3 scale(1.1f, 1.2f, 0.8f); //scale vector

        float scaleIncrement = scaleSpeed * seconds_elapsed; //scaling increment

        if (model.M[0][0] < scale.x) { //we increment the scaling until it reaches its target scale (scale vector defined)
            model.M[0][0] += scaleIncrement;
        }
        if (model.M[1][1] < scale.y) {
            model.M[1][1] += scaleIncrement;
        }
        if (model.M[2][2] < scale.z) {
            model.M[2][2] += scaleIncrement;
        }
    }

}
