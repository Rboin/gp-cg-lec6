#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "vector.h"
#include "lecture_6.h"

/**
 * This file contains declarations for variables that are used in lecture_6.h and lecture_6.cpp.
 * The actual rendering and the transformations also happen in lecture_6.cpp.
 */

float pos_x = 100, pos_y = 200, size_x = 800, size_y = 600;


SDL_Window *lec_6::window;
SDL_Renderer *renderer;
SDL_GLContext context;

float f = 0.2f;

using namespace lec_6;
int lec_6::count = 8;

vec lec_6::model_vec[] = {
        {f,  f,  f,  1.0f},
        {f,  -f, f,  1.0f},
        {-f, -f, f,  1.0f},
        {-f, f,  f,  1.0f},

        {f,  f,  -f, 1.0f},
        {f,  -f, -f, 1.0f},
        {-f, -f, -f, 1.0f},
        {-f, f,  -f, 1.0f},
};

vec lec_6::axis[4] = {
        {0,   0,   0,   1},
        {0.5, 0,   0,   1},
        {0,   0.5, 0,   1},
        {0,   0,   0.5, 1}
};

vec *lec_6::cube_buffer;
vec *lec_6::axis_buffer;
vec lec_6::position;
float lec_6::rot_x = 0, lec_6::rot_y = 0, lec_6::rot_z = 0;
float lec_6::_scale = 1.0f;
float lec_6::r = 10.0f;

// This is our field of view in radians
float lec_6::d = M_PI / 3;

float lec_6::theta = -90.0f;
float lec_6::phi = -90.0f;


bool init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << " Failed to open SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_window() {
    window = SDL_CreateWindow("Lecture 6", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size_x, size_y,
                              SDL_WINDOW_OPENGL);

    if (!window) {
        std::cout << " Failed to open window: " << SDL_GetError() << std::endl;
        return false;
    }
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    return true;
}

bool create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << " Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool set_opengl_attributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    return true;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer())
        return false;
    set_opengl_attributes();
    SDL_GL_SetSwapInterval(1);

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    return true;
}


int main(int argc, char *args[]) {
    // Create vector array

    position = {0, 0, 0, 1};

    cube_buffer = new vec[8];
    axis_buffer = new vec[4];

    // Initialize our window.
    if (!init_everything()) {
        return -1;
    }

    // Start the render loop.
    lec_6::loop();

    // Let SDL clean the pointers.
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    exit(0);
}
