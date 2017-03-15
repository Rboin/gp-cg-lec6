#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "vector.h"

float pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 8;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_GLContext context;

float f = 0.2f;

vec model_vec[] = {
        {f,  f,  f,  1.0f},
        {f,  -f, f,  1.0f},
        {-f, -f, f,  1.0f},
        {-f, f,  f,  1.0f},

        {f,  f,  -f, 1.0f},
        {f,  -f, -f, 1.0f},
        {-f, -f, -f, 1.0f},
        {-f, f,  -f, 1.0f},
};

vec axis[4] = {
        {0,   0,   0,   1},
        {0.5, 0,   0,   1},
        {0,   0.5, 0,   1},
        {0,   0,   0.5, 1}
};

vec *axis_buffer;

vec *vectors;
vec position;
mat identity = mat();
mat MVP;
float rot_x = 0, rot_y = 0, rot_z = 0;
float _scale = 1.0f;
float r = 10.0f;

// This is our field of view in radians
float d = M_PI / 3;

float theta = -90.0f;
float phi = -90.0f;

void transform_vectors() {
    // Do our normal model = T * R * S
    mat T = translate(position);
    mat R = rotate_x(rot_x) * rotate_y(rot_y) * rotate_z(rot_z);
    mat S = scale(_scale * 10); // scale up a little more
    mat model = T * R * S;

    // Create our inverse m_view matrix (converting degrees to radians)
    mat m_view = inverse_view(r, phi * M_PI / 180, theta * M_PI / 180);
    // Create our model_view matrix
    mat model_view = m_view * model;

    // Transform our axis to show on screen.
    for (int j = 0; j < 4; j++) {
        vec tmp = axis[j] * model_view;
        // Divide our fov by z
        float fov = std::tan(d / tmp.z);
        mat m_projection = projection(fov);
        axis_buffer[j] = (tmp * m_projection);
    }

    // Transform our cube to show on screen.
    for (int i = 0; i < count; i++) {
        vec tmp = model_vec[i] * model_view;
        float fov = std::tan(d / tmp.z);
        mat m_projection = projection(fov);
        vectors[i] = (tmp * m_projection);
    }
}

void render() {
    transform_vectors();

    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Draw axis
    glBegin(GL_LINES);
    glColor4ub(255, 0, 0, 255);
    glVertex2f(axis_buffer[0].x, axis_buffer[0].y);
    glVertex2f(axis_buffer[1].x, axis_buffer[1].y);
    glColor4ub(0, 255, 0, 255);
    glVertex2f(axis_buffer[0].x, axis_buffer[0].y);
    glVertex2f(axis_buffer[2].x, axis_buffer[2].y);
    glColor4ub(0, 0, 255, 255);
    glVertex2f(axis_buffer[0].x, axis_buffer[0].y);
    glVertex2f(axis_buffer[3].x, axis_buffer[3].y);

    // Draw cube
    glColor4ub(0, 0, 0, 255);

    glVertex2f(vectors[0].x, vectors[0].y);
    glVertex2f(vectors[1].x, vectors[1].y);

    glVertex2f(vectors[1].x, vectors[1].y);
    glVertex2f(vectors[2].x, vectors[2].y);

    glVertex2f(vectors[2].x, vectors[2].y);
    glVertex2f(vectors[3].x, vectors[3].y);

    glVertex2f(vectors[3].x, vectors[3].y);
    glVertex2f(vectors[0].x, vectors[0].y);

    glVertex2f(vectors[4].x, vectors[4].y);
    glVertex2f(vectors[5].x, vectors[5].y);

    glVertex2f(vectors[5].x, vectors[5].y);
    glVertex2f(vectors[6].x, vectors[6].y);

    glVertex2f(vectors[6].x, vectors[6].y);
    glVertex2f(vectors[7].x, vectors[7].y);

    glVertex2f(vectors[7].x, vectors[7].y);
    glVertex2f(vectors[4].x, vectors[4].y);

    glVertex2f(vectors[0].x, vectors[0].y);
    glVertex2f(vectors[4].x, vectors[4].y);

    glVertex2f(vectors[1].x, vectors[1].y);
    glVertex2f(vectors[5].x, vectors[5].y);

    glVertex2f(vectors[2].x, vectors[2].y);
    glVertex2f(vectors[6].x, vectors[6].y);

    glVertex2f(vectors[3].x, vectors[3].y);
    glVertex2f(vectors[7].x, vectors[7].y);

    glEnd();

    SDL_GL_SwapWindow(window);
}


// Render loop
void render_screen() {
    bool loop = true, animation = false, shrinking = false, r_x = false, r_y = false;
    int phase = 0;

    float begin = -90.0f;
    while (loop) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                loop = false;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a) {
                    animation = true;
                    phase = 1;
                }
            }
        }

        if (animation) {
            switch (phase) {
                case 1:
                    theta--;
                    if (!shrinking && _scale < 1.5f) {
                        _scale += 0.01f;
                    } else if (shrinking && _scale > 1.0f) {
                        _scale -= 0.01f;
                    }

                    if (_scale >= 1.5f) shrinking = true;
                    else if (_scale <= 1.0f) {
                        shrinking = false;
                        phase++;
                    }
                    break;
                case 2:
                    theta--;
                    if (!r_x && rot_x < M_PI / 4) {
                        rot_x += M_PI / 180;
                    } else if (r_x && rot_x >= 0.0f) {
                        rot_x -= M_PI / 180;
                    }
                    if (rot_x >= M_PI / 4) r_x = true;
                    else if (rot_x <= 0.0f) {
                        r_x = false;
                        phase++;
                    }
                    break;
                case 3:
                    phi++;
                    if (!r_y && rot_y < M_PI / 4) {
                        rot_y += M_PI / 180;
                    } else if (r_y && rot_y >= 0.0f) {
                        rot_y -= M_PI / 180;
                    }
                    if (rot_y >= M_PI / 4) r_y = true;
                    else if (rot_y <= 0.0f) {
                        r_y = false;
                        phase++;
                    }
                    break;
                case 4:
                    if (theta < begin)
                        theta++;
                    if (phi > begin)
                        phi--;
                    if (theta >= begin && phi <= begin)
                        phase = 1;
                    break;

                default:
                    break;
            }
            transform_vectors();
        }
        render();
        SDL_Delay(50);
    }


}

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

    vectors = new vec[8];
    axis_buffer = new vec[4];

    // Initialize our window.
    if (!init_everything()) {
        return -1;
    }

    // Start the render loop.
    render_screen();

    // Let SDL clean the pointers.
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}