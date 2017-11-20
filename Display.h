//
// Created by debowin on 11/12/17.
//

#ifndef GAMEGL_DISPLAY_H
#define GAMEGL_DISPLAY_H

#include <string>
#include "SDL2/SDL.h"

class Display {
    int m_width, m_height;
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    bool m_fullScreen;
public:
    virtual ~Display();

    void Update();

    void Clear(float r, float g, float b, float a);

    Display(int width, int height, std::string title);

    int GetWidth();

    int GetHeight();

    void toggleFullScreen();
};


#endif //GAMEGL_DISPLAY_H
