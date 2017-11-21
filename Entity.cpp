//
// Created by debowin on 11/16/17.
//

#include "Entity.h"

void Entity::InitWall(const Transform &transform) {
    m_mesh.InitMesh("../res/wall.obj");
    m_texture.InitTexture("../res/bricks.bmp");
    m_transform = transform;
    // TODO: use different materials
    m_material.InitMaterial("../res/key.mtl");
    m_type = TYPE_WALL;
}

void Entity::InitFloor(const Transform &transform) {
    m_mesh.InitMesh("../res/cube.obj");
    m_texture.InitTexture("../res/floor.bmp");
    m_transform = transform;
    // TODO: use different materials
    m_material.InitMaterial("../res/key.mtl");
    m_type = TYPE_FLOOR;
}

void Entity::InitDoor(const Transform &transform, char marker) {
    m_mesh.InitMesh("../res/door.obj");
    m_texture.InitTexture("../res/" + std::string(1, marker) + ".bmp");
    m_transform = transform;
    // TODO: use different materials
    m_material.InitMaterial("../res/key.mtl");
    m_type = TYPE_DOOR;
    m_marker = marker;
}

void Entity::InitKey(const Transform &transform, char marker) {
    m_mesh.InitMesh("../res/key.obj");
    m_texture.InitTexture("../res/" + std::string(1, marker) + ".bmp");
    m_transform = transform;
    // TODO: use different materials
    m_material.InitMaterial("../res/key.mtl");
    m_type = TYPE_KEY;
    m_marker = marker;
}

void Entity::InitGoal(const Transform &transform) {
    m_mesh.InitMesh("../res/ring.obj");
    m_texture.InitTexture("../res/glass.bmp");
    m_transform = transform;
    // TODO: use different materials
    m_material.InitMaterial("../res/key.mtl");
    m_type = TYPE_GOAL;
}

Entity::Entity() {
    m_type = TYPE_NONE;
}

void Entity::Draw(Shader &shader, Camera &camera) {
    shader.UpdateUniforms(m_transform, camera, m_material);
    m_texture.Bind(0);
    m_mesh.Draw();
}

void Entity::UpdateMarker(char marker) {
    m_marker = marker;
    m_texture.InitTexture("../res/" + std::string(1, m_marker) + ".bmp");
}
