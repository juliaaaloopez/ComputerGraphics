#pragma once
#include "image.h"


class ParticleSystem {

    static const int MAX_PARTICLES = 500; //num of particles we will draw 

    struct Particle { //attributes of a particle
        Vector2 position;
        Vector2 velocity; 
        Color color;
        float acceleration;
        float ttl; // time that it appears in the frambuffer before disappearing
        bool inactive; //if particle appears or not in the frambuffer
    };

    Particle particles[MAX_PARTICLES]; //array of particles

public:

    ParticleSystem() {}
    void Init();
    void Render(Image* framebuffer); 
    void Update(float dt);
};