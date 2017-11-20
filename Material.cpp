//
// Created by debowin on 11/14/17.
//

#include "Material.h"
#include <fstream>
#include <iostream>

Material::Material(std::string fileName) {
    InitMaterial(std::move(fileName));
}

const glm::vec3 &Material::GetDiffuse() const {
    return m_diffuse;
}

const glm::vec3 &Material::GetSpecular() const {
    return m_specular;
}

const glm::vec3 &Material::GetAmbient() const {
    return m_ambient;
}

const float &Material::GetNS() const{
    return m_ns;
}

Material::Material() {
    m_ambient = glm::vec3(0, 0.4, 0);
    m_diffuse = glm::vec3(0, 0.4, 0);
    m_specular = glm::vec3(0.8, 0.8, 0.8);
    m_ns = 96;
}

void Material::InitMaterial(std::string fileName) {
    std::ifstream input(fileName);

    if(input.fail())
        std::cout << "Can't open mtl file '" << fileName << "'" << std::endl;

    std::string word;

    while(input >> word) {
        if (word == "Ka")
            input >> m_ambient.r >> m_ambient.g >> m_ambient.b;
        else if (word == "Kd")
            input >> m_diffuse.r >> m_diffuse.g >> m_diffuse.b;
        else if (word == "Ks")
            input >> m_specular.r >> m_specular.g >> m_specular.b;
        else if (word == "Ns")
            input >> m_ns;
    }
}
