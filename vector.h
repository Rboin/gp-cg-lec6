//
// Created by robin on 2/20/17.
//

#ifndef LEC_3_VECTOR_H
#define LEC_3_VECTOR_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct vec;
struct mat;

/**
 * The Matrix structure.
 */
struct mat {
    float x1, x2, x3, x4,
            y1, y2, y3, y4,
            z1, z2, z3, z4,
            w1, w2, w3, w4;

    // Constructors
    mat();

    mat(vec);

    mat(vec, float);

    mat(float, float, float, float);

    mat(float x1, float x2, float x3, float x4,
        float y1, float y2, float y3, float y4,
        float z1, float z2, float z3, float z4,
        float w1, float w2, float w3, float w4);

    mat operator*(float);

    vec operator*(vec);

    mat operator*(mat);

    mat operator+(mat);

    mat operator-(mat);
};

/**
 * The Vector structure.
 */
struct vec {
    float x, y, z, w;

    vec operator+(const vec &v);

    vec operator+=(const vec &v);

    vec operator*(mat);

    vec operator*(float);
};

// ================ HELPER FUNCTIONS ================
mat scale(float);

mat scale(float, float, float);

mat rotate_x(float);

mat rotate_y(float);

mat rotate_z(float);

mat inverse_transform_x(float);

mat inverse_transform_z(float);

mat translate(float, float, float);

mat translate(vec);

mat projection(float);

mat perspective_projection(float, float, float, float);

mat inverse_view(float, float, float);

// ==================================================


SDL_Point *vec_to_point(vec *, int);


#endif //LEC_3_VECTOR_H
