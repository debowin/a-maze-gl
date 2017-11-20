//
// Created by debowin on 11/16/17.
//

#ifndef GAMEGL_ENTITY_H
#define GAMEGL_ENTITY_H


#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Material.h"
#include "Shader.h"

enum{
    TYPE_NONE,
    TYPE_START,
    TYPE_GOAL,
    TYPE_WALL,
    TYPE_DOOR,
    TYPE_KEY,
    TYPE_FLOOR
};

class Entity {
    Mesh m_mesh;
    Texture m_texture;
    Transform m_transform;
    Material m_material;
    uint m_type;
    char m_marker;
public:

    Entity();

    void InitWall(const Transform &m_transform);

    void InitFloor(const Transform &m_transform);

    void InitDoor(const Transform &m_transform, char marker);

    void InitKey(const Transform &m_transform, char marker);

    void InitGoal(const Transform &m_transform);

    Mesh &GetMesh() {
        return m_mesh;
    }

    Texture &GetTexture() {
        return m_texture;
    }

    Transform &GetTransform() {
        return m_transform;
    }

    const Material &GetMaterial() const {
        return m_material;
    }

    uint &GetType() {
        return m_type;
    }

    char &GetMarker() {
        return m_marker;
    }

    void Draw(Shader &shader, Camera &camera);

    void UpdateMarker(char marker);
};


#endif //GAMEGL_ENTITY_H
