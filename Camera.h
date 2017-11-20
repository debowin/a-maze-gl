//
// Created by debowin on 11/13/17.
//

#ifndef GAMEGL_CAMERA_H
#define GAMEGL_CAMERA_H
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class Camera {
    glm::mat4 m_perspective;
    glm::mat4 m_view;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    float m_fov;
    float m_aspect;
    float m_zNear;
    float m_zFar;

public:
    Camera(glm::vec3 pos, glm::vec3 forward, float fov, float aspect, float zNear, float zFar);
    glm::mat4 GetView();
    glm::mat4 GetProjection();
    void SetPosition(glm::vec3 position);
    void SetFOV(float fov);
    glm::vec3 &GetPos();
    glm::vec3 &GetForward();

    void turn(float d);

    glm::vec3 getMove(float distance);
};


#endif //GAMEGL_CAMERA_H
