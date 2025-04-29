#include "webview/webview.h"
#include <iostream>

int main()
{
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

    webview::webview w(true, nullptr);
    w.set_title("Webview Quill Text Editor");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);

    // Bind JS -> C++: receive content from editor
    w.bind("save", [](std::string content)
           {
    std::cout << "Received from JS:\n" << content << std::endl;
    return std::string{}; });

    w.set_html(html);
    w.run();
    return 0;
}
