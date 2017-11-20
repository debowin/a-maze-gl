//
// Created by debowin on 11/17/17.
//

#ifndef GAMEGL_MAP_H
#define GAMEGL_MAP_H


#include "Entity.h"
#include "Shader.h"
#include "Display.h"
#include <string>

enum{
    STATUS_INVALID,
    STATUS_VALID,
    STATUS_COMPLETE
};

class Map {
    Entity* m_entities{};
    Entity* m_floor{};
    int m_width{}, m_height{};
    glm::vec3 m_startPos{};
    Entity m_heldKey{};

public:
    explicit Map(const std::string &fileName);

    glm::vec3 &GetStartPos();

    void Draw(Shader &shader, Camera &camera, float counter);

    int processMovement(glm::vec3 playerPosition);

    void GetCellCoords(glm::vec3 tvec3, int &x, int &z);

    bool PickUpKey(glm::vec3 position);

    int GetWidth() const {
        return m_width;
    }

    int GetHeight() const {
        return m_height;
    }
};


#endif //GAMEGL_MAP_H
