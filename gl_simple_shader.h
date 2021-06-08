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
