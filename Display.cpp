//
// Created by debowin on 11/12/17.
//
#include "glad/glad.h"
#include "Display.h"
#include <iostream>

using namespace std;

Display::Display(int width, int height, string title){
    // SDL should be initialized
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    m_fullScreen = false;
    m_width = width;
    m_height = height;

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    if (gladLoadGL()){
        cout<<"OpenGL loaded."<<endl;
        cout<<"Vendor: \t"<<glGetString(GL_VENDOR)<<endl;
        cout<<"Renderer: \t"<<glGetString(GL_RENDERER)<<endl;
        cout<<"Version: \t"<<glGetString(GL_VERSION)<<endl;
    }
    else {
        cerr<<"ERROR: Failed to initialize OpenGL context."<<endl;
        exit(-1);
    }

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT_AND_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

Display::~Display() {
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::Update() {
    SDL_GL_SwapWindow(m_window);
    SDL_SetWindowFullscreen(m_window, m_fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void Display::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Display::GetWidth() {
    return m_width;
}

int Display::GetHeight() {
    return m_height;
}

void Display::toggleFullScreen() {
    m_fullScreen = !m_fullScreen;
}
