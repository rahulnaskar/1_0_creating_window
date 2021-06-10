#include "glfw_context.h"
#include "vbo.h"
#include "gl_simple_shader.h"
#include <unistd.h>

constexpr int window_width = 800;
constexpr int window_height = 600;

using uint = unsigned int;

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
					"frag_color = vec4(0.2f, 0.3f, 0.4f, 1.0f);\n}\0";
int main() {
	glfw_context_window::glfw_win_manager gwm;
	GLFWwindow * window = gwm.create_window(window_width, window_height);


	std::unique_ptr<gl_base_shader> gss_vertex {new gl_simple_shader(GL_VERTEX_SHADER, vertex_shader_source)};
	std::unique_ptr<gl_base_shader> gss_fragment {new gl_simple_shader(GL_FRAGMENT_SHADER, fragment_shader_source)};
	
	unsigned int shader_program {0};
	shader_program = glCreateProgram();

	gss_vertex->gl_shader_attach(shader_program);
	gss_fragment->gl_shader_attach(shader_program);

	float vertices[] = {
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		0.0f, -1.0f, 0.0f,
		-1.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
	};

	uint VAO1;
	glGenVertexArrays(1, &VAO1);
	
	glBindVertexArray(VAO1);

	gl_vbo vbo(GL_ARRAY_BUFFER);
	vbo.gl_vbo_set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);

	if (nullptr != window) {
		int x {0};
		while (false == gwm.should_close()) {
			x += 1;
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shader_program);
			glBindVertexArray(VAO1);
			if (x % 2 == 0) {
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			else {
				glDrawArrays(GL_TRIANGLES, 3, 3);
			}
			glfwSwapBuffers(window);
			glfwPollEvents();
			sleep(2);
		}
	}


	return 0;
}
