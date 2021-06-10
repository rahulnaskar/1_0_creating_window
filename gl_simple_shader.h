#include "gl_shaders.h"

class gl_simple_shader: public gl_base_shader {
	public:
	gl_simple_shader(GLenum p_shader_type, const char * p_shader_source) : shader_type(p_shader_type), shader_source(p_shader_source) {
		shader = glCreateShader(p_shader_type);
		glShaderSource(shader, 1, &shader_source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
			std::cerr << "Error in creating shader, " << p_shader_type << "," << info_log;
		}
		else {
			std::cout << "Shader created successfully" << std::endl;
		}
		
	
	}
	int gl_shader_attach(unsigned int& shader_program) {
		glAttachShader(shader_program, shader);
		glLinkProgram(shader_program);
		int success {0};
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader_program, 512, NULL, info_log);
			std::cout << "Error occurred," << info_log << std::endl;
		}
		glDeleteShader(shader);
		return success;
	}
	virtual unsigned int gl_shader() {
		return shader;	
	}
	
	private:
	const char * shader_source;
	GLenum shader_type;
	unsigned int shader {0};
	int success {0};
	char info_log[512];
}; 
