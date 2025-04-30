#include "keyCallBack.h"
#include <iostream>

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize the requied lib\n");
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, "Text Editor", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwSetKeyCallback(window, key_callback);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
