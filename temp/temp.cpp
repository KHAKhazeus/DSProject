//
// Created by Khazeus on 2018-12-25.
//
std::ofstream jsFile;
#ifdef _WIN32
jsFile.open("..\\maze\\graph.html");
#else
jsFile.open("../maze/graph.html");
#endif
jsFile << "<!DOCTYPE html>\n"
"<html>\n"
"  <head>\n"
"    <meta charset=\"utf-8\">\n"
"    <title>一个简单的关系图</title>\n"
"    <!-- 引入 G6 文件 -->\n"
"    <script src=\"./g6.js\"></script>\n"
"  </head>\n"
"  <body>\n"
"    <!-- 创建图容器 -->\n"
"    <div id=\"mountNode\"></div>\n"
"    <script>\n"
"      const data = {\n"
"        nodes: [{\n"
"          id: 'node1',\n"
"          x: 100,\n"
"          y: 200\n"
"       },{\n"
"          id: 'node2',\n"
"          x: 300,\n"
"          y: 200\n"
"       }],\n"
"        edges: [{\n"
"          id: 'edge1',\n"
"          target: 'node2',\n"
"          source: 'node1'\n"
"       }]\n"
"      };\n"
"      const graph = new G6.Graph({\n"
"        container: 'mountNode',\n"
"        width: 500,\n"
"        height: 500\n"
"      });\n"
"      graph.read(data);\n"
"    </script>\n"
"  </body>\n"
"</html>";
jsFile.close();

return 0;
}
