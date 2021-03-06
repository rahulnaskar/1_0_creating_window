#include "glfw_context.h"
#include "vbo.h"
#include "gl_simple_shader.h"
//#include <unistd.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <glm/mat4x4.hpp> // glm::mat4

constexpr int window_width = 800;
constexpr int window_height = 600;


const char* vertex_shader_source = R"GLSL(
#version 330 core
layout (location = 0) in vec4 apos;
layout (location = 1) in vec4 acol;

uniform mat4 transformaxisz;
uniform mat4 transformaxisx;
out vec4 vertex_colors;
void main() {
  vertex_colors = acol;

  gl_Position = transformaxisx * transformaxisz * vec4(apos.x, apos.y, apos.z, apos.w);
  //gl_Position = vec4(bpos.x, bpos.y, bpos.z, 1.0f);
}
)GLSL";
const char * fragment_shader_source = R"GLSL(
#version 330 core
in vec4 vertex_colors;
out vec4 frag_color;
                                       
void main() {
  frag_color = vertex_colors;
}
)GLSL";

constexpr double MM_PI = 3.14159265358979323846;  /* pi */

constexpr float radians(float x) {return x * MM_PI / 180.0f;}
constexpr float degrees(float x) {return x * 180.0f / MM_PI;}
float hypotenuse(float x, float y) {return std::sqrt(x * x + y * y);}

int main() {
  glfw_context_window::glfw_win_manager gwm;
  GLFWwindow * window = gwm.create_window(window_width, window_height);


  std::unique_ptr<gl_base_shader> gss_vertex {new gl_simple_shader(GL_VERTEX_SHADER, vertex_shader_source)};
  std::unique_ptr<gl_base_shader> gss_fragment {new gl_simple_shader(GL_FRAGMENT_SHADER, fragment_shader_source)};

  unsigned int shader_program {0};
  shader_program = glCreateProgram();

  gss_vertex->gl_shader_attach(shader_program);
  gss_fragment->gl_shader_attach(shader_program);

  glm::vec3 v3 = glm::vec3(0.0f, 0.5f, 0.0f);


  glm::mat4 m1 = glm::scale(glm::mat4(2.0f), v3);
  //std::cout << m1.x << "," << m1.y << "," << m1.z << std::endl;

  struct attribs {
    glm::vec4 lines[6];
    glm::vec4 colors[6];
    
    attribs() : lines {
        {0.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
        {0.00f, 0.0f, 1.0f, 1.0f}
      }, colors {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.00f, 0.0f, 1.0f, 1.0f}
      } {}
  } attrs;


  float vertices[] = {
    0.0f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.0f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };

//  lines[1] = matrix_2 * lines[1];
  gl_vbo vbo_base_lines(GL_ARRAY_BUFFER);
  vbo_base_lines.gl_vbo_set_data(&attrs, sizeof(attrs), GL_STATIC_DRAW);

  uint VAOBase;
  glGenVertexArrays(1, &VAOBase);
  glBindVertexArray(VAOBase);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void *>(reinterpret_cast<const char *>(&attrs.lines) - reinterpret_cast<const char *>(&attrs)));
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void *>(reinterpret_cast<const char *>(&attrs.colors) - reinterpret_cast<const char *>(&attrs)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  gl_vbo vbo(GL_ARRAY_BUFFER);
  vbo.gl_vbo_set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

#if 0
  uint VAO1;
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * 0, (void *) 0);

  glEnableVertexAttribArray(0);


  uint VAO2;
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 1, (void *) 36);
#endif


  glEnableVertexAttribArray(0);


  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  glm::mat4 matrix_z = glm::mat4(1.0);
  glm::mat4 matrix_x = glm::mat4(1.0);
  
  glm::ivec3 acceleration(0);

  if (nullptr != window) {

    glfwSetWindowUserPointer(window, &acceleration);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      glm::ivec3 *acceleration = static_cast<glm::ivec3 *>(glfwGetWindowUserPointer(window));
      switch(key) {
      case GLFW_KEY_A:
        ++acceleration->z;
        break;
      case GLFW_KEY_D:
        --acceleration->z;
        break;
      case GLFW_KEY_W:
        ++acceleration->x;
        break;
      case GLFW_KEY_S:
        --acceleration->x;
        break;
      }
    });

    while (false == gwm.should_close()) {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shader_program);

      unsigned int sl_transformer_z = glGetUniformLocation(shader_program, "transformaxisz");
      unsigned int sl_transformer_x = glGetUniformLocation(shader_program, "transformaxisx");
      //std::cout << "Transformer location, " << sl_transformer_x << std::endl;
      //std::cout << "Transformer location, " << sl_transformer_z << std::endl;


      matrix_z = glm::rotate(matrix_z, radians(0.1f * acceleration.z), glm::vec3(0.0f, 0.0f, 1.0f));
      matrix_x = glm::rotate(matrix_x, radians(0.1f * acceleration.x), glm::vec3(1.0f, 0.0f, 0.0f));
      //matrix_x = glm::rotate(matrix_x, radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));


      //unsigned int sl_transformer_z = glGetUniformLocation(shader_program, "transformaxisz");
      //unsigned int sl_transformer_x= glGetUniformLocation(shader_program, "transformaxisx");

      glUniformMatrix4fv(sl_transformer_z, 1, GL_FALSE, glm::value_ptr(matrix_z));
      glUniformMatrix4fv(sl_transformer_x, 1, GL_FALSE, glm::value_ptr(matrix_x));
      //glUniformMatrix4fv(sl_transformer_x, 1, GL_FALSE, glm::value_ptr(matrix_x));
      glBindVertexArray(VAOBase);

      glDrawArrays(GL_LINES, 0, 6);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }


  return 0;
}
