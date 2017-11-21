//
// Created by debowin on 11/12/17.
//

#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(std::string fileName) {
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int m_shader: m_shaders)
        glAttachShader(m_program, m_shader);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed");

    m_uniforms[MODEL_U] = (GLuint)glGetUniformLocation(m_program, "model");
    m_uniforms[VIEW_U] = (GLuint)glGetUniformLocation(m_program, "view");
    m_uniforms[PROJECTION_U] = (GLuint)glGetUniformLocation(m_program, "proj");
    m_uniforms[SPECULAR_U] = (GLuint)glGetUniformLocation(m_program, "material.specular");
    m_uniforms[NS_U] = (GLuint)glGetUniformLocation(m_program, "material.shininess");
}

Shader::~Shader() {
    for (unsigned int m_shader : m_shaders) {
        glDetachShader(m_program, m_shader);
        glDeleteShader(m_shader);
    }

    glDeleteProgram(m_program);
}

void Shader::Bind() {
    glUseProgram(m_program);
}

std::string Shader::LoadShader(std::string fileName) {
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE) {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), nullptr, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(std::string text, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr << "Error: Shader creation failed." << std::endl;

    const GLchar* shaderSourceString = text.c_str();
    auto shaderSourceStringLength = (GLint)text.length();

    glShaderSource(shader, 1, &shaderSourceString, &shaderSourceStringLength);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

    return shader;
}

void Shader::UpdateUniforms(const Transform &transform, Camera& camera, const Material& material) {
    glm::mat4 model = transform.GetModel();
    glm::mat4 view = camera.GetView();
    glm::mat4 proj = camera.GetProjection();
    glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &proj[0][0]);
    glUniform3fv(m_uniforms[SPECULAR_U], 1, &material.GetSpecular()[0]);
    glUniform1f(m_uniforms[NS_U], material.GetNS());
}

void Shader::setVec3(const std::string &key, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(m_program, key.c_str()), 1, &value[0]);
}

void Shader::setFloat(const std::string &key, float value) {
    glUniform1f(glGetUniformLocation(m_program, key.c_str()), value);
}
