#include "gl_includes.h"
class gl_base_shader {
	public:
	virtual unsigned int gl_shader() = 0;
	virtual int gl_shader_attach(unsigned int&) = 0;
};

