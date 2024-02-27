#include "material.h"

void Material::Enable(const sUniformData& uniformData){
    shader->Enable();
    shader->SetUniform3("u_Ka", Ka);
    shader->SetUniform3("u_Kd", Kd);
    shader->SetUniform3("u_Ks", Ks);
    shader->SetFloat("u_a", a);
    if(texture_normal != nullptr){
        shader->SetTexture("u_texture_normal", texture_normal);
    }
    if(texture_color != nullptr){
        shader->SetTexture("u_texture_color", texture_color);
    }
}

void Material::Disable(){
    shader->Disable();
}


