#pragma once
#include <Utilities/AException.h>

namespace gl {
	class GLException: public utils::AException {
		public:
			GLException(const std::string& message);
			virtual ~GLException(void) throw ();
	};
}

