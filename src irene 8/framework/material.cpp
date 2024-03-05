#include "material.h"

void Material::Enable(const sUniformData& uniformData, int light_index) {
    shader->Enable();

    //Material
    shader->SetVector3("u_Ka", Ka);
    shader->SetVector3("u_Kd", Kd);
    shader->SetVector3("u_Ks", Ks);
    shader->SetFloat("u_a", a);
    if (texture_normal != nullptr) {
        shader->SetTexture("u_texture_normal", texture_normal);
    }
    if (texture_color != nullptr) {
        shader->SetTexture("u_texture_color", texture_color);
    }

    shader->SetMatrix44("u_model", uniformData.model);
    shader->SetMatrix44("u_viewprojection", uniformData.viewprojection_matrix);
    shader->SetVector3("u_camera_position", uniformData.camera_position);
    shader->SetVector3("u_ambientLight", uniformData.ambient_light);

    shader->SetVector2("u_lightPosition", uniformData.lights[light_index].position);
    shader->SetVector3("u_diffuseIntensity", uniformData.lights[light_index].diffuse_intensity);
    shader->SetVector3("u_specularIntensity", uniformData.lights[light_index].specular_intensity);
}

void Material::Disable() {
    shader->Disable();
}

