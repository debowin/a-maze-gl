//
// Created by debowin on 11/13/17.
//

#ifndef GAMEGL_TEXTURE_H
#define GAMEGL_TEXTURE_H

#include <string>
#include "glad/glad.h"

class Texture {
    GLuint m_texture;
public:
    explicit Texture(std::string fileName);

    void InitTexture(std::string fileName);

    Texture();

    void Bind(uint unit);
    virtual ~Texture();
};


#endif //GAMEGL_TEXTURE_H
