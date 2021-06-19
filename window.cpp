#include "glfw_context.h"
#include "vbo.h"
#include "gl_simple_shader.h"
#include <unistd.h>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <glm/mat4x4.hpp> // glm::mat4

constexpr int window_width = 800;
constexpr int window_height = 600;


const char * vertex_shader_source = 	"#version 330 core\n"
                                        "layout (location = 0) in vec3 apos;\n"
                                        //				"layout (location = 1) in vec3 bpos;\n"
                                        "void main() {\n"
                                        "gl_Position = vec4(apos.x, apos.y, apos.z, 1.0f);\n"
                                        //				"gl_Position = vec4(bpos.x, bpos.y, bpos.z, 1.0f);\n"
                                        "}\0";
const char * fragment_shader_source = "#version 330 core\n"
                                      "out vec4 frag_color;\n"
                                      "void main() {\n"
                                      "frag_color = vec4(0.2f, 1.0f, 0.4f, 1.0f);\n}\0";

constexpr double MM_PI = 3.14159265358979323846;  /* pi */

constexpr double radians(double x) {return x * MM_PI / 180.0f;}
constexpr double degrees(double x) {return x * 180.0f / MM_PI;}
constexpr double hypotenuse(double x, double y) {return sqrt(x * x + y * y);}

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

  glm::vec3 lines[] = {
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.00f, 0.0f, 1.0f}
  };

  float vertices[] = {
    0.0f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.0f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };

  glm::vec3 test_vec3(10.0f, 10.0f, 0.0f);
  glm::vec3 test_vec3_copy = glm::normalize(test_vec3);
  std::cout << test_vec3_copy.x << "," << test_vec3_copy.y << "," << test_vec3_copy.z << ",degrees," << degrees(asin(test_vec3_copy.x))<< std::endl;

  glm::mat4 matrix_1 = glm::mat4(1.0);
  int i = 0;
  for ( ; i < 4; i++) {
    const auto& x = matrix_1[i];
    std::cout << "matrix, " << i << "x, " << matrix_1[i].x << ". y, " << matrix_1[i].y << ". z, " << matrix_1[i].z << ". w, " << matrix_1[i].w << std::endl;
  }

  constexpr double test_value = 45.0f;
  lines[1].x = cos(radians(test_value));
  lines[1].y = sin(radians(test_value));

  std::cout << "sin " << std::fixed << test_value << ", " << std::fixed << cos(radians(test_value)) << std::endl;
  std::cout << "cos " << test_value << ", " << std::fixed << sin(radians(test_value)) << std::endl;
  std::cout << "tan " << test_value << ", " << std::fixed << tan(radians(test_value)) << std::endl;

  double height {3.0};
  double base {4.0};

  double hyp = hypotenuse(base, height);
  std::cout << "Hypotenuse," << hyp << std::endl;

  std::cout << "acos test_value, " << std::fixed << degrees(acos(0)) << std::endl;
  std::cout << "asin 45, " << std::fixed << degrees(asin(0)) << std::endl;
  std::cout << "atan 5, " << std::fixed << degrees(atan(0)) << std::endl;
  gl_vbo vbo_base_lines(GL_ARRAY_BUFFER);
  vbo_base_lines.gl_vbo_set_data(lines, sizeof(lines), GL_STATIC_DRAW);

  uint VAOBase;
  glGenVertexArrays(1, &VAOBase);
  glBindVertexArray(VAOBase);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
  glEnableVertexAttribArray(0);

  gl_vbo vbo(GL_ARRAY_BUFFER);
  vbo.gl_vbo_set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

  uint VAO1;
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * 0, (void *) 0);

  glEnableVertexAttribArray(0);


  uint VAO2;
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * 0, (void *) 36);


  glEnableVertexAttribArray(0);


  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  if (nullptr != window) {
    int x {0};
    while (false == gwm.should_close()) {
      x += 1;
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shader_program);

      glBindVertexArray(VAOBase);
      glDrawArrays(GL_LINES, 0, 6);
      /*
      glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shader_program);
      glBindVertexArray(VAO1);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(VAO2);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      */
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }


  return 0;
}
