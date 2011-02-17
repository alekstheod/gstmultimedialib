#include "GLException.h"

namespace gl{
	GLException::GLException(const std::string& message) : utils::AException(message) {
	}

	GLException::~GLException(void)throw () {
	}
}

