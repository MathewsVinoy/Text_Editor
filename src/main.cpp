#include <GLFW/glfw3.h>
#include "webview/webview.h"
#include <iostream>

// Callback function to handle GLFW errors
void error_callback(int error, const char *description)
{
  std::cerr << "Error: " << description << std::endl;
}

int main()
{
  // Initialize GLFW
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Set GLFW error callback
  glfwSetErrorCallback(error_callback);

  // Create a GLFW window
  GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW Webview Integration", nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // HTML content
  const char *html = R"""(
  <!DOCTYPE html>
  <html>
    <head>
      <link href="https://cdn.quilljs.com/1.3.6/quill.snow.css" rel="stylesheet">
      <style>
        #editor-container {
          height: 300px;
          border: 1px solid #ccc;
          margin-bottom: 10px;
        }
      </style>
    </head>
    <body>
      <div id="editor-container"></div>
      <button onclick="saveContent()">Save</button>

      <script src="https://cdn.quilljs.com/1.3.6/quill.min.js"></script>
      <script>
        var quill = new Quill('#editor-container', {
          theme: 'snow'
        });

        function saveContent() {
          const content = quill.root.innerHTML;
          window.external.invoke(content);
        }
      </script>
    </body>
  </html>
  )""";

  // Create a webview
  webview::webview w(true, nullptr);
  w.set_title("Webview Quill Text Editor");
  w.set_size(800, 600, WEBVIEW_HINT_NONE);

  // Bind JS -> C++: receive content from editor
  w.bind("save", [](std::string content)
         {
        std::cout << "Received from JS:\n" << content << std::endl;
        return std::string{}; });

  w.set_html(html);

  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    // Poll for and process events
    glfwPollEvents();

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the webview
    w.render();

    // Swap front and back buffers
    glfwSwapBuffers(window);
  }

  // Terminate GLFW
  glfwTerminate();

  return 0;
}
