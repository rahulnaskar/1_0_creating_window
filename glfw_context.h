#include "gl_includes.h"

#include <iostream>
#include <memory>

namespace glfw_context_window {
	void framebuffer_size_callback(GLFWwindow * win, int width, int height) { 
		glViewport(0, 0, width, height);
	}
	class glfw_win_manager {
		GLFWwindow * window {nullptr};
		void process_input(GLFWwindow * win) {
			if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(win, true);
			}
		}
		public:
		GLFWwindow * create_window(size_t window_width, size_t window_height) {
			window = glfwCreateWindow(window_width, window_height, "First window", nullptr, nullptr);
			if (nullptr == window) {
				std::cerr << "Failed to create OpenGL window" << std::endl;
				glfwTerminate();
			}
			glfwMakeContextCurrent(window);
			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				std::cerr << "Failed to initialize GLAD" << std::endl;
			}
			glViewport(0, 0, window_width, window_height);
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			return window;
		}
		bool should_close() {
			process_input(window);
			return glfwWindowShouldClose(window);
		}
		glfw_win_manager() {
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
		virtual ~glfw_win_manager() {
			std::cout << "Closing GL window" << std::endl;
			glfwTerminate();
		}
	};

}
