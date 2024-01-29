#include "entity.h"


void Entity::Render(Image* framebuffer, Camera* camera, const Color& c){

    std::vector<Vector3> vertices = mesh->GetVertices();
    
    for(int i = 0; i<vertices.size(); i+=3){
        bool negZ0, negZ1, negZ2;
        Vector3 t0 = model*vertices[i];
        Vector3 t1= model*vertices[i+1];
        Vector3 t2= model*vertices[i+2];
        Vector3 p0 = camera->ProjectVector(t0, negZ0);
        Vector3 p1 = camera->ProjectVector(t1, negZ1);
        Vector3 p2 = camera->ProjectVector(t2, negZ2);
        
        if(!negZ0 && !negZ1 && !negZ2){ //si triangle està dins frame
            p0.x = (p0.x + 1.0f) * 0.5f * framebuffer->width; //to convert from clip range [-1, 1] to screen range [0, 1]
            p0.y = (p0.y + 1.0f) * 0.5f * framebuffer->height;
            p1.x = (p1.x + 1.0f) * 0.5f * framebuffer->width;
            p1.y = (p1.y + 1.0f) * 0.5f * framebuffer->height;
            p2.x = (p2.x + 1.0f) * 0.5f * framebuffer->width;
            p2.y = (p2.y + 1.0f) * 0.5f * framebuffer->height;
            
            Vector3 v0 = p0;
            Vector3 v1 = p1;
            Vector3 v2 = p2;
            
            framebuffer->DrawLineDDA(v0.x, v0.y, v1.x, v1.y, c);
            framebuffer->DrawLineDDA(v1.x, v1.y, v2.x, v2.y, c);
            framebuffer->DrawLineDDA(v2.x, v2.y, v0.x, v0.y, c);
        }
        
    }

}
