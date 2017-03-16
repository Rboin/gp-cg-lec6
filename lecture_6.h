//
// Created by robin on 3/16/17.
//

#ifndef LEC_6_DRAW_H
#define LEC_6_DRAW_H

#include "vector.h"

namespace lec_6 {
    // Variables are declared in main.cpp
    extern float rot_x;
    extern float rot_y;
    extern float rot_z;
    extern float _scale;
    extern float r;
    // This is our fov in radians (60 degrees)
    extern float d;
    extern float theta;
    extern float phi;

    extern int count;

    extern vec model_vec[];

    extern vec axis[4];

    extern vec position;

    extern vec *axis_buffer;
    extern vec *cube_buffer;

    extern SDL_Window *window;


    void transform_vectors();

    void draw_axis();

    void draw_cube();

    void render();

    void loop();
};

#endif //LEC_6_DRAW_H
