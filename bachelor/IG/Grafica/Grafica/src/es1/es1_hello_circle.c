#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include "../callbacks.h"
#include "../init_window.h"
#include "../shader_boilerplate.h"

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    GLFWwindow* window = init_window(SCR_WIDTH, SCR_HEIGHT, "Hello Circle");

    // callbacks
    // ---------
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int shaderProgram = init_shaders();

#define CIRCLE_VERTS 100
    float circle_radius = 0.5;
    float circle_verts[(CIRCLE_VERTS + 2) * 3];
    // center
    circle_verts[0] = 0.0f;
    circle_verts[1] = 0.0f;
    circle_verts[2] = 0.0f;

    for (int i = 0; i <= CIRCLE_VERTS; i++) // <=: last vertex == first vertex
    {
        float angle = ((float) i) / CIRCLE_VERTS * 2.0F * 3.14159F;
        float x =  cosf(angle) * circle_radius;
        float y = sinf(angle) * circle_radius;
        circle_verts[(i + 1) * 3 + 0] = x;
        circle_verts[(i + 1) * 3 + 1] = y;
        circle_verts[(i + 1) * 3 + 2] = 0.0f;
    }

    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle_verts), circle_verts, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLint colorUniformLocation = glGetUniformLocation(shaderProgram,"color");

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform4f(colorUniformLocation, 1.0f, 0.5f, 0.2f, 1.0f);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_VERTS + 2);
        glBindVertexArray(0);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwWaitEventsTimeout(0.01);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}
