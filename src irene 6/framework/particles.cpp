// particles.cpp
#include "particles.h"

#include <cstdlib> 
#include <ctime>   


void ParticleSystem::Init() {
    srand(time(nullptr)); // to generate random numbers

    for (int i = 0; i < MAX_PARTICLES; ++i) {
        particles[i].position.x = rand() % 720; // random x position within bounds of frambuffer
        particles[i].position.y = rand() % 420; // same as before, but y position
        particles[i].velocity = Vector2((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f); // Random velocity vector between 0 and 1
        particles[i].color = Color(rand() % 256, rand() % 256, rand() % 256); // Random color
        particles[i].acceleration = (float)(rand() % 100) / 1000.0f; // Random acceleration
        particles[i].ttl = (float)(rand() % 100) / 50.0f; // Random time to live
        particles[i].inactive = false; // Set particle as active
    }    
}

void ParticleSystem::Render(Image* framebuffer) {
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (!particles[i].inactive) { //If particle is active, we draw it in the framebuffer
            framebuffer->SetPixelSafe(particles[i].position.x, particles[i].position.y, particles[i].color);
        }
        
    }
}

void ParticleSystem::Update(float dt) {
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (!particles[i].inactive) {

            particles[i].position.x = particles[i].position.x + particles[i].velocity.x * dt; //updating position following motion equation
            particles[i].position.y = particles[i].position.y + particles[i].velocity.y * dt;

            particles[i].ttl -= dt; // we decrease the time to live of the particle

            // if time to live ends, the particle becomes inactive
            if (particles[i].ttl <= 0) {
                particles[i].inactive = true; 
            }
        }
    }
}
