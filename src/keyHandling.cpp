#include "keyCallBack.h"
#include <iostream>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        printf("Value :- %d\n", key);
    }
}
