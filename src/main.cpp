#include <iostream>
#include <GL/glew.h>
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <oglplus/interop/glm.hpp>
#include <vector>


int main(void)
{

  using namespace oglplus;
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glewInit();

  Context gl;
  auto s = gl.Version();

  // Vertex shader
  VertexShader vs;
  // Fragment shader
  FragmentShader fs;
  // Program
  Program prog;
  // A vertex array object for the rendered triangle
  VertexArray triangle;
  // VBO for the triangle's vertices
  Buffer verts;

  vs.Source(" \
#version 330\n \
      in vec3 Position; \
      void main(void) \
      { \
      gl_Position = vec4(Position, 1.0); \
      } \
      ");
    // compile it
    try{
      vs.Compile();
    }
  catch(CompileError c){
    std:: cout << c.Log() << std::endl;
  }
  // set the fragment shader source
  fs.Source(" \
#version 330\n \
      uniform vec2 Color; \
      out vec4 fragColor; \
      void main(void) \
      { \
      fragColor = vec4(Color.x,0.0, 1.0, 1.0); \
      } \
      ");
    // compile it
    fs.Compile();
  // attach the shaders to the program
  prog.AttachShader(vs);
  prog.AttachShader(fs);
  // link and use it
  prog.Link();
  prog.Use();

  auto v = glm::vec2(1.,0.);
  Uniform<glm::vec2>(prog,"Color").Set(v);
  using myvec = glm::tvec2<float,glm::precision::mediump>;

  // bind the VAO for the triangle
  triangle.Bind()
    ;
  GLfloat triangle_verts[9] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  // bind the VBO for the triangle vertices
  verts.Bind(Buffer::Target::Array);
  // upload the data
  Buffer::Data(Buffer::Target::Array, 9, triangle_verts);
  // setup the vertex attribs array for the vertices
  VertexArrayAttrib vert_attr(prog, "Position");
  vert_attr.Setup<GLfloat>(3);
  vert_attr.Enable();
  gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gl.Disable(Capability::DepthTest);
  /* Loop until the user closes the window */
  //u.SetValue(v);

  while (!glfwWindowShouldClose(window))
  {
    /* Render here */

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    gl.Clear().ColorBuffer();
    gl.DrawArrays(PrimitiveType::Triangles, 0, 3);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
