//
// Created by debowin on 11/13/17.
//

#include "Transform.h"
#include "glm/gtx/transform.hpp"

glm::vec3 &Transform::GetTrans() {
    return m_trans;
}

glm::vec3 &Transform::GetRot() {
    return m_rot;
}

glm::vec3 &Transform::GetScale() {
    return m_scale;
}

glm::mat4 Transform::GetModel() const {
    glm::mat4 transMatrix = glm::translate(m_trans);
    glm::mat4 scaleMatrix = glm::scale(m_scale);
    glm::mat4 rotMatrix = glm::rotate(m_angle, m_rot);

    return transMatrix * rotMatrix * scaleMatrix;
}

float &Transform::GetAngle() {
    return m_angle;
}
