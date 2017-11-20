//
// Created by debowin on 11/13/17.
//

#ifndef GAMEGL_TRANSFORM_H
#define GAMEGL_TRANSFORM_H


#include <glm/glm.hpp>

class Transform {
    glm::vec3 m_trans, m_rot, m_scale;
    float m_angle;
public:
    explicit Transform(const glm::vec3 &trans = glm::vec3(), const glm::vec3 &rot = glm::vec3(1, 1, 1),
                         const glm::vec3 &scale = glm::vec3(1, 1, 1), const float &angle = 0):
                                                                                m_trans(trans), m_rot(rot),
                                                                                m_scale(scale), m_angle(angle) {}
    glm::vec3 &GetTrans();

    glm::vec3 &GetRot();

    float &GetAngle();

    glm::vec3 &GetScale();

    glm::mat4 GetModel() const;
};


#endif //GAMEGL_TRANSFORM_H
