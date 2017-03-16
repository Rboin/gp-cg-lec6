//
// Created by robin on 3/16/17.
//

#include "lecture_6.h"
#include <GL/glew.h>
#include <SDL_timer.h>
#include <SDL_events.h>

namespace lec_6 {

    void render() {
        transform_vectors();
        // Clear our screen
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        draw_axis();
        draw_cube();

        SDL_GL_SwapWindow(window);
    }

    void draw_axis() {
        glBegin(GL_LINES);
        {
            glColor4ub(255, 0, 0, 255);
            glVertex2f(axis_buffer[0].x, axis_buffer[0].y);
            glVertex2f(axis_buffer[1].x, axis_buffer[1].y);
            glColor4ub(0, 255, 0, 255);
            glVertex2f(axis_buffer[0].x, axis_buffer[0].y);
            glVertex2f(axis_buffer[2].x, axis_buffer[2].y);
            glColor4ub(0, 0, 255, 255);
            glVertex2f(axis_buffer[0].x, axis_buffer[0].y);
            glVertex2f(axis_buffer[3].x, axis_buffer[3].y);
        }
        glEnd();
    }

    void draw_cube() {
        glBegin(GL_LINES);
        {
            glColor4ub(0, 0, 0, 255);

            glVertex2f(cube_buffer[0].x, cube_buffer[0].y);
            glVertex2f(cube_buffer[1].x, cube_buffer[1].y);

            glVertex2f(cube_buffer[1].x, cube_buffer[1].y);
            glVertex2f(cube_buffer[2].x, cube_buffer[2].y);

            glVertex2f(cube_buffer[2].x, cube_buffer[2].y);
            glVertex2f(cube_buffer[3].x, cube_buffer[3].y);

            glVertex2f(cube_buffer[3].x, cube_buffer[3].y);
            glVertex2f(cube_buffer[0].x, cube_buffer[0].y);

            glVertex2f(cube_buffer[4].x, cube_buffer[4].y);
            glVertex2f(cube_buffer[5].x, cube_buffer[5].y);

            glVertex2f(cube_buffer[5].x, cube_buffer[5].y);
            glVertex2f(cube_buffer[6].x, cube_buffer[6].y);

            glVertex2f(cube_buffer[6].x, cube_buffer[6].y);
            glVertex2f(cube_buffer[7].x, cube_buffer[7].y);

            glVertex2f(cube_buffer[7].x, cube_buffer[7].y);
            glVertex2f(cube_buffer[4].x, cube_buffer[4].y);

            glVertex2f(cube_buffer[0].x, cube_buffer[0].y);
            glVertex2f(cube_buffer[4].x, cube_buffer[4].y);

            glVertex2f(cube_buffer[1].x, cube_buffer[1].y);
            glVertex2f(cube_buffer[5].x, cube_buffer[5].y);

            glVertex2f(cube_buffer[2].x, cube_buffer[2].y);
            glVertex2f(cube_buffer[6].x, cube_buffer[6].y);

            glVertex2f(cube_buffer[3].x, cube_buffer[3].y);
            glVertex2f(cube_buffer[7].x, cube_buffer[7].y);
        }
        glEnd();
    }

    void transform_vectors() {
        // Do our normal model = T * R * S
        mat T = translate(position);
        mat R = rotate_x(rot_x * (M_PI / 180)) * rotate_y(rot_y * (M_PI / 180)) * rotate_z(rot_z * (M_PI / 180));
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
            cube_buffer[i] = (tmp * m_projection);
        }
    }

    void loop() {
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

            // The animation
            if (animation) {
                switch (phase) {
                    case 1:
                        theta--;
                        if (!shrinking && _scale < 1.5f) {
                            _scale += 0.01f;
                        } else if (shrinking && _scale > 1.0f) {
                            _scale -= 0.01f;
                        }

                        if (_scale - 1.5f >= 0.0f) shrinking = true;
                        else if (_scale - 1.0f <= 0.0f) {
                            shrinking = false;
                            phase++;
                        }
                        break;
                    case 2:
                        theta--;
                        if (!r_x && rot_x < 45.0f) {
                            rot_x++;
                        } else if (r_x && rot_x > 0.0f) {
                            rot_x--;
                        }
                        if (rot_x >= 45.0f) r_x = true;
                        else if (rot_x <= 0.0f) {
                            r_x = false;
                            phase++;
                        }
                        break;
                    case 3:
                        phi++;
                        if (!r_y && rot_y < 45.0f) {
                            rot_y++;
                        } else if (r_y && rot_y > 0.0f) {
                            rot_y--;
                        }
                        if (rot_y >= 45.0f) r_y = true;
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
            }
            render();
            SDL_Delay(50);
        }


    }
};
