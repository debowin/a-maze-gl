//
// Created by debowin on 11/13/17.
//

#include "Mesh.h"

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Mesh::Mesh(Vertex *vertices, uint numVertices, uint *indices, uint numIndices) {
    IndexedModel model;
    for (uint i = 0; i < numVertices; i++) {
        model.positions.push_back(vertices[i].pos);
        model.texCoords.push_back(vertices[i].texCoord);
        model.normals.push_back(vertices[i].normal);
    }

    for (uint i = 0; i < numIndices; i++) {
        model.indices.push_back(indices[i]);
    }
    LoadMesh(model);
}

Mesh::Mesh(std::string fileName) {
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    LoadMesh(model);
}

void Mesh::InitMesh(std::string fileName){
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    LoadMesh(model);
}

void Mesh::LoadMesh(IndexedModel &model) {
    m_drawCount = (uint) model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexBufferObjects);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_VB]);

    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0],
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[TEXCOORD_VB]);

    glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0],
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(TEXCOORD_VB);
    glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferObjects[INDEX_VB]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[NORMAL_VB]);

    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0],
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(NORMAL_VB);
    glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}

Mesh::Mesh() = default;

Vertex::Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord, const glm::vec3 &normal) :
        pos(pos), texCoord(texCoord), normal(normal) {}
