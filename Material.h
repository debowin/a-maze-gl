//
// Created by debowin on 11/14/17.
//

#ifndef GAMEGL_MATERIAL_H
#define GAMEGL_MATERIAL_H


#include <glm/glm.hpp>
#include <string>

class Material {
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    glm::vec3 m_ambient;

    float m_ns;
public:
    explicit Material(std::string fileName);

    void InitMaterial(std::string fileName);

    Material();

    const glm::vec3 &GetDiffuse() const;

    const glm::vec3 &GetSpecular() const;

    const glm::vec3 &GetAmbient() const;

    const float &GetNS() const;

};


#endif //GAMEGL_MATERIAL_H
