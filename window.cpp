
#include "glfw_context.h"

constexpr int window_width = 800;
constexpr int window_height = 600;

int main() {
	glfw_context_window::glfw_win_manager gwm;
	GLFWwindow * window = gwm.create_window(window_width, window_height);
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
