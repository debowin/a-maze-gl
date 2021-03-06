//
// Created by debowin on 11/14/17.
//

#include "Light.h"

Light::Light(const glm::vec3 &m_color) : m_color(m_color) {}

const glm::vec3 &Light::GetColor() const {
    return m_color;
}

PointLight::PointLight(const glm::vec3 &m_color, const glm::vec3 &m_position, uint index) :
        Light(m_color), m_position(m_position), m_index(index) {}

DirectionalLight::DirectionalLight(const glm::vec3 &m_color, const glm::vec3 &m_direction) :
        Light(m_color), m_direction(m_direction) {}

void DirectionalLight::SetShaderUniform(Shader shader, Camera camera) {
    shader.setVec3("directionalLight.color", m_color);
    shader.setVec3("directionalLight.direction", (camera.GetView() * glm::vec4(m_direction, 0)).xyz());
}

void PointLight::SetShaderUniform(Shader shader, Camera camera) {
    std::string prefix = "pointLights";
    prefix += "[" + std::to_string(m_index) + "].";
    shader.setVec3(prefix + "color", m_color);
    shader.setVec3(prefix + "position", (camera.GetView() * glm::vec4(m_position, 1)).xyz());
}

SpotLight::SpotLight(const glm::vec3 &color, const glm::vec3 &position, const glm::vec3 &direction,
                     const float cutOffTheta, const float cutOffGamma) : Light(color), m_position(position),
                                                                         m_direction(direction),
                                                                         m_cutOffTheta(cutOffTheta),
                                                                         m_cutOffGamma(cutOffGamma) {}

void SpotLight::SetShaderUniform(Shader shader, Camera camera) {
    shader.setVec3("spotLight.color", m_color);
    shader.setVec3("spotLight.position", (camera.GetView() * glm::vec4(m_position, 1)).xyz());
    shader.setVec3("spotLight.direction", (camera.GetView() * glm::vec4(m_direction, 0)).xyz());
    shader.setFloat("spotLight.cutOffTheta", m_cutOffTheta);
    shader.setFloat("spotLight.cutOffGamma", m_cutOffGamma);
}

glm::vec3 &SpotLight::GetDirection() {
    return m_direction;
}

glm::vec3 &SpotLight::GetPosition() {
    return m_position;
}
