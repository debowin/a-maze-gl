//
// Created by debowin on 11/17/17.
//

#include "Map.h"
#include <fstream>

Map::Map(const std::string &fileName) {
    std::ifstream in;
    in.open(fileName);
    char element;
    in >> m_width >> m_height;
    m_entities = new Entity[m_height * m_width];
    m_floor = Entity();

    // parse maze map file
    Transform floorTransform;
    floorTransform.GetTrans() = glm::vec3(0, -0.5f, -m_height/2.f);
    floorTransform.GetScale() = glm::vec3(m_width, 1, m_height);
    m_floor.InitFloor(floorTransform);
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            int index = i * m_width + j;
            in >> element;
            if (element == 'W') {
                // wall
                Transform wallTransform;
                wallTransform.GetTrans() = glm::vec3(j - m_width / 2.0f + 0.5f, 0.5f, i + 0.5f - m_height);
                m_entities[index].InitWall(wallTransform);
            } else if (element == 'G') {
                // goal
                Transform goalTransform;
                goalTransform.GetTrans() = glm::vec3(j - m_width / 2.0f + 0.5f, 0.5f, i + 0.5f - m_height);
                m_entities[index].InitGoal(goalTransform);
            } else if (element == 'S') {
                // start
                m_startPos = glm::vec3(j - m_width / 2.0f + 0.5f, 0.65f, i + 0.5f - m_height);
            } else if (element >= 'A' && element < 'F') {
                // door
                Transform doorTransform;
                doorTransform.GetTrans() = glm::vec3(j - m_width / 2.0f + 0.5f, 0.5f, i + 0.5f - m_height);
                m_entities[index].InitDoor(doorTransform, (char) std::tolower(element));
            } else if (element >= 'a' && element < 'f') {
                // key
                Transform keyTransform;
                keyTransform.GetTrans() = glm::vec3(j - m_width / 2.0f + 0.5f, 0.5f, i + 0.5f - m_height);
                m_entities[index].InitKey(keyTransform, element);
            }
        }
    }
}

void Map::Draw(Shader &shader, Camera &camera, float counter) {
    // render all game entities
    m_floor.Draw(shader, camera);
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            int index = i * m_width + j;
            uint type = m_entities[index].GetType();
            if (type != TYPE_NONE) {
                if (type == TYPE_KEY)
                    m_entities[index].GetTransform().GetAngle() = counter * 3.14f / 2;
                else if (type == TYPE_GOAL)
                    m_entities[index].GetTransform().GetAngle() = -counter * 3.14f;
                else if (type == TYPE_DOOR &&
                         ((index - m_width >= 0 && m_entities[index - m_width].GetType() == TYPE_WALL)
                          || (index + m_width < m_height * m_width &&
                              m_entities[index + m_width].GetType() == TYPE_WALL))) {
                    // if needed, flip a door by 90 degrees based on the walls around it.
                    m_entities[index].GetTransform().GetAngle() = (float) M_PI / 2.f;
                    m_entities[index].GetTransform().GetRot() = glm::vec3(0, 1, 0);
                }
                m_entities[index].Draw(shader, camera);
            }
        }
    }
    if (m_heldKey.GetType() == TYPE_KEY) {
        // render held key
        m_heldKey.GetTransform().GetTrans() = camera.GetPos() + camera.GetForward() * glm::vec3(0.175f, 0.175f, 0.175f)
                                              + glm::vec3(0.f, -0.05f, 0.f);
        m_heldKey.GetTransform().GetScale() = glm::vec3(0.3f, 0.3f, 0.3f);
        float angle = -acosf(glm::dot(glm::normalize(camera.GetForward()),
                                      glm::vec3(-1.f, 0.f, 0.f)));
        // if angle is negative, detect and account for it since acos of dot product cant
        if (glm::dot(glm::vec3(0, 1, 0),
                     glm::cross(glm::normalize(camera.GetForward()),
                                glm::vec3(-1.f, 0.f, 0.f))) < 0.f)
            angle = -angle;
        m_heldKey.GetTransform().GetAngle() = angle;
        m_heldKey.GetTransform().GetRot() = glm::vec3(0.f, 1.f, 0.f);
        m_heldKey.Draw(shader, camera);
    }
}

glm::vec3 &Map::GetStartPos() {
    return m_startPos;
}

int Map::processMovement(glm::vec3 playerPosition) {
    int cellX, cellZ;
    GetCellCoords(playerPosition, cellX, cellZ);
    if (cellX < 0 || cellX >= m_width || cellZ < 0 || cellZ >= m_height)
        // suicidal much?
        return STATUS_INVALID;
    if (m_entities[cellZ * m_width + cellX].GetType() == TYPE_WALL)
        // cant walk through walls, dummy
        return STATUS_INVALID;
    else if (m_entities[cellZ * m_width + cellX].GetType() == TYPE_DOOR) {
        if (m_entities[cellZ * m_width + cellX].GetMarker() == m_heldKey.GetMarker()) {
            // what's behind door number one?
            m_heldKey.GetType() = TYPE_NONE;
            m_entities[cellZ * m_width + cellX].GetType() = TYPE_NONE;
            return STATUS_VALID;
        }
        // you shall not pass!
        return STATUS_INVALID;
    } else if (m_entities[cellZ * m_width + cellX].GetType() == TYPE_GOAL) {
        // winner winner, chicken dinner
        return STATUS_COMPLETE;
    }
    // you go, bro
    return STATUS_VALID;
}

void Map::GetCellCoords(glm::vec3 pos, int &x, int &z) {
    x = static_cast<int>(floorf(pos.x + m_width / 2.f));
    z = static_cast<int>(m_height + floorf(pos.z));
}

bool Map::PickUpKey(glm::vec3 position) {
    int cellX, cellZ;
    GetCellCoords(position, cellX, cellZ);
    if (m_entities[cellZ * m_width + cellX].GetType() == TYPE_KEY) {
        // if we're in a key cell
        if (m_heldKey.GetType() == TYPE_NONE) {
            // pick up key
            m_heldKey.InitKey(Transform(), m_entities[cellZ * m_width + cellX].GetMarker());
            m_entities[cellZ * m_width + cellX].GetType() = TYPE_NONE;
        } else {
            // switch keys
            char temp = (m_heldKey.GetMarker());
            m_heldKey.UpdateMarker(m_entities[cellZ * m_width + cellX].GetMarker());
            m_entities[cellZ * m_width + cellX].UpdateMarker(temp);
        }
    }
}
