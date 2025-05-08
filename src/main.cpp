#include "webview/webview.h"
#include <iostream>
#include <fstream>
#include <string>

std::string readFile(const std::string &filePath)
{
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    return "";
  }
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}

void writeFile(const std::string &filePath, const std::string &content)
{
  std::ofstream file(filePath);
  if (file.is_open())
  {
    file << content;
    file.close();
  }
}

int main()
{
  const char *html = R"""(
    <!DOCTYPE html>
    <html>
    <head>
      <meta charset='UTF-8'>
      <title>VS Code Clone</title>
      <style>
        * {
          margin: 0;
          padding: 0;
          box-sizing: border-box;
          font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', 'Noto Sans', Helvetica, Arial, sans-serif;
          user-select: none;
        }

        body {
          display: flex;
          flex-direction: column;
          height: 100vh;
          overflow: hidden;
          background-color: #1e1e1e;
          color: #d4d4d4;
        }

        /* Top menu bar */
        .menubar {
          height: 30px;
          background-color: #3c3c3c;
          display: flex;
          align-items: center;
          padding: 0 10px;
          color: #cccccc;
          font-size: 12px;
          border-bottom: 1px solid #252525;
        }

        .menu-item {
          padding: 0 8px;
          cursor: pointer;
        }

        .menu-item:hover {
          background-color: #505050;
        }

        /* Main content area */
        .main-container {
          display: flex;
          flex: 1;
          overflow: hidden;
        }

        /* Activity Bar (leftmost) */
        .activity-bar {
          width: 48px;
          background-color: #333333;
          display: flex;
          flex-direction: column;
          align-items: center;
          padding-top: 10px;
        }

        .activity-icon {
          width: 48px;
          height: 48px;
          display: flex;
          justify-content: center;
          align-items: center;
          cursor: pointer;
          color: #858585;
          font-size: 24px;
        }

        .activity-icon.active {
          color: #ffffff;
          border-left: 2px solid #ffffff;
        }

        .activity-icon:hover {
          color: #ffffff;
        }

        /* Side Bar */
        .sidebar {
          width: 250px;
          background-color: #252526;
          display: flex;
          flex-direction: column;
          border-right: 1px solid #1e1e1e;
        }

        .sidebar-header {
          padding: 10px;
          font-size: 11px;
          text-transform: uppercase;
          font-weight: bold;
          letter-spacing: 0.5px;
          color: #bbbbbb;
        }

        .explorer {
          flex: 1;
          overflow-y: auto;
          padding: 0 0 10px 0;
        }

        .folder {
          display: flex;
          align-items: center;
          padding: 3px 10px;
          cursor: pointer;
          font-size: 13px;
        }

        .folder:hover {
          background-color: #2a2d2e;
        }

        .folder-icon {
          margin-right: 5px;
          color: #c5c5c5;
        }

        .file {
          display: flex;
          align-items: center;
          padding: 3px 10px 3px 24px;
          cursor: pointer;
          font-size: 13px;
        }

        .file:hover {
          background-color: #2a2d2e;
        }

        .file-icon {
          margin-right: 5px;
          color: #519aba;
        }

        /* Editor Area */
        .editor-container {
          flex: 1;
          display: flex;
          flex-direction: column;
          background-color: #1e1e1e;
        }

        .tabs {
          height: 35px;
          background-color: #252526;
          display: flex;
          align-items: center;
          border-bottom: 1px solid #1e1e1e;
        }

        .tab {
          height: 100%;
          padding: 0 10px;
          display: flex;
          align-items: center;
          background-color: #2d2d2d;
          border-right: 1px solid #252526;
          cursor: pointer;
          font-size: 13px;
        }

        .tab.active {
          background-color: #1e1e1e;
        }

        .tab-icon {
          margin-right: 5px;
          color: #519aba;
        }

        .editor {
          flex: 1;
          background-color: #1e1e1e;
          padding: 10px;
          overflow: auto;
          position: relative;
        }

        #editor-content {
          border: none;
          outline: none;
          padding: 0 0 0 30px;
          background-color: #1e1e1e;
          color: #d4d4d4;
          font-family: 'Consolas', 'Courier New', monospace;
          font-size: 14px;
          white-space: pre;
          line-height: 1.5;
          tab-size: 4;
          position: relative;
          min-height: 100%;
        }

        .line-numbers {
          position: absolute;
          top: 10px;
          left: 10px;
          width: 30px;
          font-family: 'Consolas', 'Courier New', monospace;
          font-size: 14px;
          line-height: 1.5;
          color: #858585;
          text-align: right;
          padding-right: 5px;
          user-select: none;
        }

        /* Status Bar */
        .statusbar {
          height: 22px;
          background-color: #007acc;
          display: flex;
          align-items: center;
          padding: 0 10px;
          color: white;
          font-size: 12px;
        }

        .status-item {
          margin-right: 10px;
        }

        .right-status {
          margin-left: auto;
          display: flex;
        }

        .right-status .status-item {
          margin-left: 10px;
          margin-right: 0;
        }

        /* Button Panel */
        .button-panel {
          padding: 10px;
          display: flex;
          flex-wrap: wrap;
          gap: 5px;
          background-color: #252526;
          border-top: 1px solid #1e1e1e;
        }

        button {
          background-color: #0e639c;
          color: white;
          border: none;
          padding: 6px 12px;
          cursor: pointer;
          font-size: 12px;
          border-radius: 2px;
        }

        button:hover {
          background-color: #1177bb;
        }
      </style>
    </head>
    <body>
      <div class="menubar">
        <div class="menu-item">File</div>
        <div class="menu-item">Edit</div>
        <div class="menu-item">Selection</div>
        <div class="menu-item">View</div>
        <div class="menu-item">Go</div>
        <div class="menu-item">Run</div>
        <div class="menu-item">Terminal</div>
        <div class="menu-item">Help</div>
      </div>

      <div class="main-container">
        <div class="activity-bar">
          <div class="activity-icon active">📁</div>
          <div class="activity-icon">🔍</div>
          <div class="activity-icon">🔄</div>
          <div class="activity-icon">🐞</div>
          <div class="activity-icon">📦</div>
        </div>

        <div class="sidebar">
          <div class="sidebar-header">EXPLORER</div>
          <div class="explorer">
            <div class="folder">
              <span class="folder-icon">📁</span> src
            </div>
            <div class="file">
              <span class="file-icon">📄</span> main.cpp
            </div>
            <div class="file">
              <span class="file-icon">📄</span> index.html
            </div>
            <div class="file">
              <span class="file-icon">📄</span> styles.css
            </div>
            <div class="folder">
              <span class="folder-icon">📁</span> include
            </div>
            <div class="file">
              <span class="file-icon">📄</span> webview.h
            </div>
            <div class="folder">
              <span class="folder-icon">📁</span> build
            </div>
          </div>
        </div>

        <div class="editor-container">
          <div class="tabs">
            <div class="tab active">
              <span class="tab-icon">📄</span> main.cpp
            </div>
          </div>

          <div class="editor">
            <div class="line-numbers" id="line-numbers"></div>
            <div id="editor-content" contenteditable="true" spellcheck="false"></div>
          </div>

          <div class="button-panel">
            <button onclick="execCmd('bold')">Bold</button>
            <button onclick="execCmd('italic')">Italic</button>
            <button onclick="execCmd('underline')">Underline</button>
            <button onclick="save()">Save Content</button>
            <button onclick="openFile()">Open File</button>
          </div>
        </div>
      </div>

      <div class="statusbar">
        <div class="status-item">Ready</div>
        <div class="status-item">Ln 1, Col 1</div>
        <div class="right-status">
          <div class="status-item">UTF-8</div>
          <div class="status-item">C++</div>
          <div class="status-item">Spaces: 4</div>
        </div>
      </div>

      <script>
        // Initialize with some code content
        const initialCode = `#include "webview/webview.h"\n#include <iostream>\n\nint main() {\n    // Your code here\n    std::cout << "Hello, VS Code Clone!" << std::endl;\n    return 0;\n}`;

        const editorContent = document.getElementById('editor-content');
        editorContent.textContent = initialCode;

        // Generate line numbers
        function updateLineNumbers() {
          const lines = editorContent.textContent.split('\n');
          const lineNumbers = document.getElementById('line-numbers');
          lineNumbers.innerHTML = '';

          for (let i = 1; i <= lines.length; i++) {
            lineNumbers.innerHTML += i + '<br>';
          }
        }

        // Initial line numbers
        updateLineNumbers();

        // Update line numbers when content changes
        editorContent.addEventListener('input', updateLineNumbers);

        function execCmd(command) {
          document.execCommand(command, false, null);
        }

        function save() {
          const content = document.getElementById('editor-content').innerHTML;
          window.external.invoke(JSON.stringify({
            action: 'save',
            content: content
          }));
        }

        function openFile() {
          window.external.invoke(JSON.stringify({
            action: 'open'
          }));
        }

        // Track cursor position
        editorContent.addEventListener('keyup', updateCursorPosition);
        editorContent.addEventListener('click', updateCursorPosition);

        function updateCursorPosition() {
          const selection = window.getSelection();
          if (selection.rangeCount > 0) {
            const range = selection.getRangeAt(0);
            const position = getCursorPosition(range);
            document.querySelector('.statusbar .status-item:nth-child(2)').textContent =
              `Ln ${position.line}, Col ${position.column}`;
          }
        }

        function getCursorPosition(range) {
          const content = editorContent.textContent.substring(0, range.startOffset);
          const lines = content.split('\n');
          const line = lines.length;
          const column = lines[lines.length - 1].length + 1;
          return { line, column };
        }
      </script>
    </body>
    </html>
    )""";

  webview::webview w(true, nullptr);
  w.set_title("VS Code Clone");
  w.set_size(1000, 700, WEBVIEW_HINT_NONE);
  w.bind("external", [](const std::string &invoke_arg)
         {
        try {
            std::cout << "Received: " << invoke_arg << std::endl;
            return std::string("Started");
        } catch (const std::exception& e) {
            std::cerr << "Error processing content: " << e.what() << std::endl;
            return std::string("{Error}");
        } });

  w.set_html(html);
  w.run();
  return 0;
}
