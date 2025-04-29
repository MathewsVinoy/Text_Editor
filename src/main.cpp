#include "webview/webview.h"
#include "iostream"
int main()
{
    // HTML page with a simple contentEditable div
    const char *html = R"""(
    <!DOCTYPE html>
    <html>
    <head>
      <meta charset='UTF-8'>
      <title>Mini Text Editor</title>
      <style>
        body { font-family: sans-serif; padding: 20px; background: #f4f4f4; }
        #editor {
          border: 1px solid #ccc;
          padding: 10px;
          background: white;
          height: 300px;
          overflow-y: auto;
        }
        button {
          margin-top: 10px;
          padding: 10px;
        }
      </style>
    </head>
    <body>
      <h2>HTML Text Editor</h2>
      <div id="editor" contenteditable="true">Edit this text...</div>
      <br/>
      <button onclick="save()" > Save Content</ button>

                       <script>
                           function save()
    {
        const content = document.getElementById('editor').innerHTML;
        window.external.invoke(content);
    }
      </script>
    </body>
    </html>
  )""";

    // Create the webview window
    webview::webview w(true, nullptr);
    w.set_title("C++ HTML Text Editor");
    w.set_size(600, 500, WEBVIEW_HINT_NONE);

    // Bind the callback: JS sends content → C++
    w.bind("external", [](const std::string &content)
           {
    printf("Saved content:\n%s\n", content.c_str());
    return ""; });

    w.set_html(html);
    w.run();
    return 0;
}
