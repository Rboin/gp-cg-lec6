//
// Created by robin on 2/20/17.
//

#include <cmath>
#include "vector.h"

vec vec::operator+(const vec &v) {
    return {x + v.x, y + v.y, z + v.z, (float) ((w + v.w) == 2)};
}

vec vec::operator+=(const vec &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w = (float) ((w + v.w) == 2);

    return *this;
}

vec vec::operator*(mat m) {
    return m * (*this);
}

vec vec::operator*(float f) {
    return {x * f, y * f, z * f, w};
}

mat::mat() : mat(1, 1, 1, 1) {}

mat::mat(struct vec v) : mat(v.x, v.y, v.z, 1) {}

mat::mat(struct vec v, float w) : mat(v.x, v.y, v.z, w) {}

mat::mat(float x, float y, float z, float w) :
        x1(x), x2(0), x3(0), x4(0),
        y1(0), y2(y), y3(0), y4(0),
        z1(0), z2(0), z3(z), z4(0),
        w1(0), w2(0), w3(0), w4(w) {}

mat::mat(float x1, float x2, float x3, float x4,
         float y1, float y2, float y3, float y4,
         float z1, float z2, float z3, float z4,
         float w1, float w2, float w3, float w4) : x1(x1), x2(x2), x3(x3), x4(x4),
                                                   y1(y1), y2(y2), y3(y3), y4(y4),
                                                   z1(z1), z2(z2), z3(z3), z4(z4),
                                                   w1(w1), w2(w2), w3(w3), w4(w4) {}

mat mat::operator*(float f) {
    return {
            x1 * f, x2 * f, x3 * f, x4 * f,
            y1 * f, y2 * f, y3 * f, y4 * f,
            z1 * f, z2 * f, z3 * f, z4 * f,
            w1 * f, w2 * f, w3 * f, w4 * f
    };
}

vec mat::operator*(vec v) {
    return {
            x1 * v.x + x2 * v.y + x3 * v.z + x4 * v.w,
            y1 * v.x + y2 * v.y + y3 * v.z + y4 * v.w,
            z1 * v.x + z2 * v.y + z3 * v.z + z4 * v.w,
            w1 * v.x + w2 * v.y + w3 * v.z + w4 * v.w,
    };
}

mat mat::operator*(mat m) {
    return {
            x1 * m.x1 + x2 * m.y1 + x3 * m.z1 + x4 * m.w1, x1 * m.x2 + x2 * m.y2 + x3 * m.z2 + x4 * m.w2,
            x1 * m.x3 + x2 * m.y3 + x3 * m.z3 + x4 * m.w3, x1 * m.x4 + x2 * m.y4 + x3 * m.z4 + x4 * m.w4,

            y1 * m.x1 + y2 * m.y1 + y3 * m.z1 + y4 * m.w1, y1 * m.x2 + y2 * m.y2 + y3 * m.z2 + y4 * m.w2,
            y1 * m.x3 + y2 * m.y3 + y3 * m.z3 + y4 * m.w3, y1 * m.x4 + y2 * m.y4 + y3 * m.z4 + y4 * m.w4,

            z1 * m.x1 + z2 * m.y1 + z3 * m.z1 + z4 * m.w1, z1 * m.x2 + z2 * m.y2 + z3 * m.z2 + z4 * m.w2,
            z1 * m.x3 + z2 * m.y3 + z3 * m.z3 + z4 * m.w3, z1 * m.x4 + z2 * m.y4 + z3 * m.z4 + z4 * m.w4,

            w1 * m.x1 + w2 * m.y1 + w3 * m.z1 + w4 * m.w1, w1 * m.x2 + w2 * m.y2 + w3 * m.z2 + w4 * m.w2,
            w1 * m.x3 + w2 * m.y3 + w3 * m.z3 + w4 * m.w3, w1 * m.x4 + w2 * m.y4 + w3 * m.z4 + w4 * m.w4,
    };
}

mat mat::operator+(mat m) {
    return {
            x1 + m.x1, x2 + m.x2, x3 + m.x3, x4 + m.x4,
            y1 + m.y1, y2 + m.y2, y3 + m.y3, y4 + m.y4,
            z1 + m.z1, z2 + m.z2, z3 + m.z3, z4 + m.z4,
            w1 + m.w1, w2 + m.w2, w3 + m.w3, w4 + m.w4
    };
}

mat mat::operator-(mat m) {
    return {
            x1 - m.x1, x2 - m.x2, x3 - m.x3, x4 - m.x4,
            y1 - m.y1, y2 - m.y2, y3 - m.y3, y4 - m.y4,
            z1 - m.z1, z2 - m.z2, z3 - m.z3, z4 - m.z4,
            w1 - m.w1, w2 - m.w2, w3 - m.w3, w4 - m.w4
    };
}

mat scale(float f) {
    return mat(f, f, f, 1);
}

mat scale(float x, float y, float z) {
    return mat(x, y, z, 1);
}

mat rotate_x(float f) {
    return {
            1, 0, 0, 0,
            0, std::cos(f), -std::sin(f), 0,
            0, std::sin(f), std::cos(f), 0,
            0, 0, 0, 1
    };
}

mat rotate_y(float f) {
    return {
            std::cos(f), 0, std::sin(f), 0,
            0, 1, 0, 0,
            -std::sin(f), 0, std::cos(f), 0,
            0, 0, 0, 1
    };
}

mat rotate_z(float f) {
    return {
            std::cos(f), -std::sin(f), 0, 0,
            std::sin(f), std::cos(f), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
}

mat transform_x(float phi) {
    return {
            1, 0, 0, 0,
            0, std::cos(phi), -std::sin(phi), 0,
            0, std::sin(phi), std::cos(phi), 0,
            0, 0, 0, 1
    };
}

mat transform_z(float theta) {
    return {
            -std::sin(theta), -std::cos(theta), 0, 0,
            std::cos(theta), -std::sin(theta), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
}

mat inverse_transform_x(float phi) {
    return {
            1, 0, 0, 0,
            0, std::cos(phi), std::sin(phi), 0,
            0, -std::sin(phi), std::cos(phi), 0,
            0, 0, 0, 1
    };
}

mat inverse_transform_z(float theta) {
    return {
            -std::sin(theta), std::cos(theta), 0, 0,
            -std::cos(theta), -std::sin(theta), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
}

mat translate(float x, float y, float z) {
    return {
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1
    };
}

mat translate(vec v) {
    return translate(v.x, v.y, v.z);
}

mat inverse_view(float r, float phi, float theta) {
    vec trans = {
            -r * std::cos(theta) * std::sin(phi),
            -r * std::sin(theta) * std::sin(phi),
            -r * std::cos(phi),
    };
    return inverse_transform_x(phi) * (inverse_transform_z(theta) * translate(trans));
}

mat projection(float f) {
    return {
            f, 0, 0, 0,
            0, f, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 1
    };
}
//
//float width = 1280, height = 900;
//float ratio = width/height;
//
//float left = -ratio, right = ratio, bottom = -1.0f, top = 1.0f;
//float far = 100.0f, near = -1.0f;
//
//float r_width = 1.0f / (right - left);
//float r_height = 1.0f / (top - bottom);
//float r_depth = 1.0f / (far - near);
//float x = 2.0f * (r_width);
//float y = 2.0f * (r_height);
//float z = 2.0f * (r_depth);
//float A = (right + left) * r_width;
//float B = (top + bottom) * r_height;
//float C = (far + near) * r_depth;

mat perspective_projection(float fov, float aspect_ratio, float near, float far) {
    float fustrum_depth = far - near;
    float depth = 1 / fustrum_depth;
    float fov_t = 1 / std::tanh(0.5f * fov);
    return {
            -1 * fov_t / aspect_ratio, 0, 0, 0,
            0, fov_t, 0, 0,
            0, 0, far * depth, 1,
            0, 0, (-far * near) * depth, 0
    };
//    return {
//            x, 0, 0, -A,
//            0, y, 0, -B,
//            0, 0, -z, -C,
//            0, 0, 0, 1.0f
//    };

}

SDL_Point *vec_to_point(vec *vectors, int size) {
    SDL_Point *points = new SDL_Point[size + 1];
    for (int i = 0; i < size; i++) {
        points[i] = {(int) vectors[i].x, (int) vectors[i].y};
    }
    points[size] = {(int) vectors[0].x, (int) vectors[0].y};
    return points;
}
