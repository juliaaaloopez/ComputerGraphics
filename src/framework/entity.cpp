#include "entity.h"

void Entity::Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer){

    std::vector<Vector3> vertices = mesh->GetVertices();
    
    

    for (int i = 0; i < vertices.size(); i += 3) {
        bool negZ0, negZ1, negZ2;
        Vector3 t0 = model * vertices[i];
        Vector3 t1 = model * vertices[i + 1]; //change of coordinates from local to world
        Vector3 t2 = model * vertices[i + 2];
        Vector3 p0 = camera->ProjectVector(t0, negZ0); //from world to clip space
        Vector3 p1 = camera->ProjectVector(t1, negZ1);
        Vector3 p2 = camera->ProjectVector(t2, negZ2);

        if (!negZ0 && !negZ1 && !negZ2) { // if the triangle is inside the frame
            p0.x = (p0.x + 1.0f) * 0.5f * framebuffer->width; //to convert from clip range [-1, 1] to screen range [0, 1]
            p0.y = (p0.y + 1.0f) * 0.5f * framebuffer->height;
            p1.x = (p1.x + 1.0f) * 0.5f * framebuffer->width;   //from clip space to camera space
            p1.y = (p1.y + 1.0f) * 0.5f * framebuffer->height;
            p2.x = (p2.x + 1.0f) * 0.5f * framebuffer->width;
            p2.y = (p2.y + 1.0f) * 0.5f * framebuffer->height;
 
            Color color0 = Color::RED; // Determine color based on the vertex
            
            /*if(plain){
                Vector2 v0 = {p0.x, p0.y};
                Vector2 v1 = {p1.x, p1.y};
                Vector2 v2 = {p2.x, p2.y};
                framebuffer->DrawTriangle(v0, v1, v2,color0, 1, color0);
                
            } else if (!plain){*/
                
                Color color1 = Color::GREEN; // Determine color based on the vertex
                Color color2 = Color::BLUE;
            
            Vector2 uv0 = mesh->GetUVs()[i];
            Vector2 uv1 = mesh->GetUVs()[i+1];
            Vector2 uv2 = mesh->GetUVs()[i+2];
            
            
            
                //For lab 3 we need to use the drawtriangle filled to render the mesh
                framebuffer->DrawTriangleInterpolated(p0, p1, p2, color0, color1, color2, zBuffer, texture, uv0, uv1, uv2); 
            //}
        }

    }

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
