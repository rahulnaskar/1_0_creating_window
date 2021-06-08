#include "glfw_context.h"
#include "vbo.h"
#include "gl_simple_shader.h"

constexpr int window_width = 800;
constexpr int window_height = 600;

const char * vertex_shader_source = 	"#version 330 core\n"
				"layout (location = 0) in vec3 apos;\n"
				"void main() {\n"
				"gl_Position = vec4(apos.x, apos.y, apos.z, 1.0f);\n}\0";
const char * fragment_shader_source = "#version 330 core\n"
					"out vec4 frag_color;\n"
					"void main() {\n"
					"frag_color = vec4(0.2f, 0.3f, 0.4f, 1.0f);\n}\0";
int main() {
	glfw_context_window::glfw_win_manager gwm;
	GLFWwindow * window = gwm.create_window(window_width, window_height);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	gl_vbo vbo(GL_ARRAY_BUFFER);
	vbo.gl_vbo_set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

	std::unique_ptr<gl_base_shader> gss_vertex {new gl_simple_shader(GL_VERTEX_SHADER, vertex_shader_source)};
	std::unique_ptr<gl_base_shader> gss_fragment {new gl_simple_shader(GL_FRAGMENT_SHADER, fragment_shader_source)};

	if (nullptr != window) {
		while (false == gwm.should_close()) {
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}


	return 0;
}
