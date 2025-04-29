// #include "keyCallBack.h"
// #include <iostream>

// int main()
// {
//     if (!glfwInit())
//     {
//         fprintf(stderr, "Failed to initialize the requied lib\n");
//         return -1;
//     }

//     GLFWwindow *window = glfwCreateWindow(640, 480, "Text Editor", NULL, NULL);
//     if (!window)
//     {
//         fprintf(stderr, "Failed to create window\n");
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);

//     while (!glfwWindowShouldClose(window))
//     {
//         glfwMakeContextCurrent(window);
//         glClear(GL_COLOR_BUFFER_BIT);
//         glfwSwapBuffers(window);
//         glfwSetKeyCallback(window, key_callback);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include "MyRenderInterface.h"
#include <Rocket/Core/SystemInterface.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Custom SystemInterface
class MySystemInterface : public Rocket::Core::SystemInterface
{
public:
    float GetElapsedTime() override
    {
        return static_cast<float>(glfwGetTime());
    }
};

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW + libRocket", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW (must come after context is made current!)
    glewExperimental = true;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << "\n";
        return -1;
    }

    // Setup libRocket
    Rocket::Core::SetRenderInterface(new MyRenderInterface());
    Rocket::Core::SetSystemInterface(new MySystemInterface());
    Rocket::Core::Initialise();
    Rocket::Controls::Initialise();

    Rocket::Core::Context *context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(800, 600));
    if (!context)
    {
        std::cerr << "Failed to create Rocket context\n";
        return -1;
    }

    Rocket::Core::ElementDocument *document = context->LoadDocument("/media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/views/index.html");
    if (document)
    {
        document->Show();
    }
    else
    {
        std::cerr << "Failed to load document: views/index.rml\n";
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // (optional) dark background
        glClear(GL_COLOR_BUFFER_BIT);

        context->Update();
        context->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    Rocket::Core::Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
