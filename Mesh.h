//
// Created by debowin on 11/13/17.
//

#ifndef GAMEGL_MESH_H
#define GAMEGL_MESH_H

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "obj_loader.h"
#include <string>

class Vertex {
public:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
    Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord, const glm::vec3 &normal);
};

class Mesh {
    enum{
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        INDEX_VB,
        NUM_BUFFERS
    };
    GLuint m_vertexArrayObject;
    GLuint m_vertexBufferObjects[NUM_BUFFERS];
    uint m_drawCount;
    void LoadMesh(IndexedModel &model);
public:
    Mesh(std::string fileName);
    Mesh(Vertex* vertices, uint numVertices, uint* indices, uint numIndices);

    Mesh();

    void Draw();

    void InitMesh(std::string fileName);

    virtual ~Mesh();
};


#endif //GAMEGL_MESH_H
