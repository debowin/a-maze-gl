//
// Created by debowin on 11/13/17.
//
#define GLM_SWIZZLE
#include <glm/gtx/transform.hpp>
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 forward, float fov, float aspect, float zNear, float zFar) {
    m_fov = fov;
    m_aspect = aspect;
    m_zNear = zNear;
    m_zFar = zFar;
    m_position = position;
    m_forward = forward;
    m_up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetProjection() {
    m_perspective = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
    return m_perspective;
}

glm::mat4 Camera::GetView() {
    m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
    return m_view;
}

void Camera::SetPosition(glm::vec3 position) {
    m_position = position;
}

void Camera::SetFOV(float fov) {
    m_fov = fov;
}

glm::vec3 &Camera::GetPos() {
    return m_position;
}

glm::vec3 &Camera::GetForward() {
    return m_forward;
}

void Camera::turn(float angle) {
    GetForward() = (glm::rotate(angle, glm::vec3(0, 1, 0)) * glm::vec4(GetForward(), 0.f)).xyz();
}

glm::vec3 Camera::getMove(float distance) {
    return (glm::translate(GetForward() * glm::vec3(distance, distance, distance)) * glm::vec4(GetPos(), 1.0f)).xyz();
}

