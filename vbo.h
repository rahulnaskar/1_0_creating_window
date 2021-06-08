#include <glad/glad.h>
#include <GLFW/glfw3.h>

class gl_vbo {
	public:
	gl_vbo(GLenum p_buff_type): buff_type(p_buff_type) {
		glGenBuffers(1, &vbo);
		glBindBuffer(buff_type, vbo);
	}
	bool gl_vbo_set_data(float data[], size_t sz,  GLenum p_draw_type) {
		glBufferData(buff_type, sz, data, p_draw_type);
		return true;
	}
	virtual ~gl_vbo() {
	}
	unsigned int get_vbo() {
		return vbo;
	}
	private:
	GLenum buff_type;
	unsigned int vbo;
};
