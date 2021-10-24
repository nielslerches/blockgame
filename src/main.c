#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <assert.h>
#include <stdio.h>

static float fovy = 60;
static float playerPosition[3] =  { 0, 0, -10 };
static float playerDirection[3] = { 0, 0,   0 };

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void) scancode;
    (void) mods;

    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_C:
                switch (glfwGetInputMode(window, GLFW_CURSOR)) {
                    case GLFW_CURSOR_HIDDEN:
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        break;
                    case GLFW_CURSOR_NORMAL:
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                        break;
                    default:
                        break;
                }
                break;
            case GLFW_KEY_W:
                playerPosition[2] += 1.0;
                break;
            case GLFW_KEY_A:
                playerPosition[0] -= 1.0;
                break;
            case GLFW_KEY_S:
                playerPosition[2] -= 1.0;
                break;
            case GLFW_KEY_D:
                playerPosition[0] += 1.0;
                break;
            case GLFW_KEY_UP:
                playerPosition[1] += 1.0;
                break;
            case GLFW_KEY_DOWN:
                playerPosition[1] -= 1.0;
                break;
            case GLFW_KEY_LEFT:
                fovy -= 10;
                break;
            case GLFW_KEY_RIGHT:
                fovy += 10;
                break;
            default:
                break;
        }
    }
}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

void drawCube()
{
    GLfloat vertices[] = 
    {
        -0.5, -0.5, -0.5,   -0.5, -0.5,  0.5,   -0.5,  0.5,  0.5,   -0.5,  0.5, -0.5,
         0.5, -0.5, -0.5,    0.5, -0.5,  0.5,    0.5,  0.5,  0.5,    0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,   -0.5, -0.5,  0.5,    0.5, -0.5,  0.5,    0.5, -0.5, -0.5,
        -0.5,  0.5, -0.5,   -0.5,  0.5,  0.5,    0.5,  0.5,  0.5,    0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,   -0.5,  0.5, -0.5,    0.5,  0.5, -0.5,    0.5, -0.5, -0.5,
        -0.5, -0.5,  0.5,   -0.5,  0.5,  0.5,    0.5,  0.5,  0.5,    0.5, -0.5,  0.5
    };

    GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 24);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display( GLFWwindow* window )
{
    while(!glfwWindowShouldClose(window))
    {
        // Scale to window size
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // Draw stuff
        glClearColor(0.0, 0.8, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluLookAt(
            playerDirection[0], playerDirection[1], playerDirection[2],
            playerPosition[0], playerPosition[1], playerPosition[2],
            0, 1, 0
        );
        // gluLookAt(
        //     0,  0, -1,
        //     0,  0,  0,
        //     0,  1,  0
        // );
        gluPerspective( fovy, (double)windowWidth / (double)windowHeight, 0.1, 100 );

        glMatrixMode(GL_MODELVIEW_MATRIX);

        glTranslatef(playerPosition[0], playerPosition[1], playerPosition[2]);

        drawCube();

        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    GLFWwindow* window = initWindow(1024, 620);
    assert(window != NULL);

    display(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
