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
    GLFWwindow* window = init_window(SCR_WIDTH, SCR_HEIGHT, "ITALIAN FLAG + CIRCLE");

    // callbacks
    // ---------
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int shaderProgram = init_shaders();

    float z = 0;
    float flagTop = 0.8F;
    float flagBottom = 0.2F;
    float totalWidth = 2;
    float quadWidth = totalWidth / 5.0F;

#define FLAG_VERTS 6 * 3 * 3

    float flag_verts[FLAG_VERTS];

    for (int i = 1; i <= 3; i++)
    {
	    float quadX = -1 + quadWidth * i;

        float quadVertTopLeft[] = {quadX, flagTop};
        float quadVertBottomLeft[] = {quadX, flagBottom};
        float quadVertTopRight[] = {quadX + quadWidth, flagTop};
        float quadVertBottomRight[] = {quadX + quadWidth, flagBottom};

        int arrOffset = (i-1) * 18;

        //For Each Vertex in double-triangle
        for (int v = 0; v < 6; v++)
        {
            for (int coord = 0; coord < 3; coord++)
            {
	            if (coord == 2)
	            {
		            flag_verts[arrOffset + v * 3 + coord] = z;
	            }
                else
                {
	                switch (v)
	                {
	                case 0:
	                case 3:
                        flag_verts[arrOffset + v * 3 + coord] = quadVertTopLeft[coord];
                        break;
	                case 1:
                        flag_verts[arrOffset + v * 3 + coord] = quadVertBottomLeft[coord];
                        break;
	                case 2:
	                case 4:
                        flag_verts[arrOffset + v * 3 + coord] = quadVertBottomRight[coord];
                        break;
	                case 5:
                        flag_verts[arrOffset + v * 3 + coord] = quadVertTopRight[coord];
	                }
                }
            }
        } 
    }

    float flag_colors[3 * 3] = {
        0, 1, 0,
        1, 1, 1,
        1, 0, 0
    };

	unsigned int flagVbo, flagVao;
    glGenVertexArrays(1, &flagVao);
    glGenBuffers(1, &flagVbo);

    glBindBuffer(GL_ARRAY_BUFFER, flagVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(flag_verts), flag_verts, GL_STATIC_DRAW);

    glBindVertexArray(flagVao);
    glBindBuffer(GL_ARRAY_BUFFER, flagVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    for (size_t i = 0; i < FLAG_VERTS; i++)
    {
	    if (i % 3 == 0)
	    {
		    printf("%d:%f,", i, flag_verts[i]);
	    }
    }
    printf("\n\n");

    for (size_t i = 0; i < 9; i++)
    {
        printf("%d:%f,", i, flag_colors[i]);
    }
    printf("\n\n");


#define CIRCLE_VERTS 100

    float circle_radius = 0.3F;
    float circle_verts[(CIRCLE_VERTS + 2) * 3];
    // center
    circle_verts[0] = 0.0f;
    circle_verts[1] = -0.5f;
    circle_verts[2] = 0.0f;

    for (int i = 0; i <= CIRCLE_VERTS; i++) // <=: last vertex == first vertex
    {
        float angle = ((float) i) / CIRCLE_VERTS * 2.0F * 3.14159F;
        float x =  cosf(angle) * circle_radius;
        float y = sinf(angle) * circle_radius - 0.5F;
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

        glBindVertexArray(flagVao);

        for (int i = 0; i < 3; i++)
        {
    		glUniform4f(colorUniformLocation, flag_colors[i * 3], flag_colors[i * 3 + 1], flag_colors[i * 3 + 2], 1.0F);
            //glUniform4f(colorUniformLocation, rand()/(float) RAND_MAX, rand()/(float) RAND_MAX, rand()/(float) RAND_MAX, 1.0F);
	        glDrawArrays(GL_TRIANGLES, 0 + i * 6, 12);
        }
        glBindVertexArray(0);

        glUniform4f(colorUniformLocation, 0.0f, 0.0f, 1.0f, 1.0f);
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
