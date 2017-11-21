//
// Created by debowin on 11/14/17.
//

#ifndef GAMEGL_LIGHT_H
#define GAMEGL_LIGHT_H

#define GLM_SWIZZLE

#include <glm/glm.hpp>
#include "Shader.h"

class Light {
public:
    glm::vec3 m_color;

    explicit Light(const glm::vec3 &m_color);

    const glm::vec3 &GetColor() const;

    virtual void SetShaderUniform(Shader shader, Camera camera) = 0;
};

class PointLight : public Light {
    glm::vec3 m_position;
    uint m_index;
public:
    PointLight(const glm::vec3 &m_color, const glm::vec3 &m_position, uint index);

    void SetShaderUniform(Shader shader, Camera camera) override;
};

class DirectionalLight : public Light {
    glm::vec3 m_direction;
public:
    DirectionalLight(const glm::vec3 &m_color, const glm::vec3 &m_direction);

    void SetShaderUniform(Shader shader, Camera camera) override;
};

class SpotLight : public Light {
    float m_cutOffTheta;
    float m_cutOffGamma;
    glm::vec3 m_position;
    glm::vec3 m_direction;
public:
    SpotLight(const glm::vec3 &m_color, const glm::vec3 &m_position, const glm::vec3 &m_direction, float cutOffTheta, float cutOffGamma);

    void SetShaderUniform(Shader shader, Camera camera) override;

    glm::vec3 &GetDirection();

    glm::vec3 &GetPosition();
};


#endif //GAMEGL_LIGHT_H
