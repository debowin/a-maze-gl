//
// Created by debowin on 11/12/17.
//

#ifndef GAMEGL_SHADER_H
#define GAMEGL_SHADER_H

#include "glad/glad.h"
#include "Transform.h"
#include "Camera.h"
#include "Material.h"
#include <string>

class Shader {
    static const uint NUM_SHADERS = 2;
    GLuint m_program;
    enum{
        MODEL_U,
        VIEW_U,
        PROJECTION_U,
        AMBIENT_U,
        DIFFUSE_U,
        SPECULAR_U,
        NS_U,
        NUM_UNIFORMS
    };
    GLuint m_uniforms[NUM_UNIFORMS];
    GLuint m_shaders[NUM_SHADERS];
public:
    explicit Shader(std::string fileName);
    void Bind();
    virtual ~Shader();
    std::string LoadShader(std::string fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
    GLuint CreateShader(std::string text, GLenum shaderType);
    void UpdateUniforms(const Transform& transform, Camera& camera, const Material& material);
    void setVec3(const std::string &key, glm::vec3 value);
    void setFloat(const std::string &key, float value);
};


#endif //GAMEGL_SHADER_H
