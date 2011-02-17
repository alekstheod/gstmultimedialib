#pragma once

namespace gl {
	class IGLModel {
		public:

			IGLModel(void) {};
			virtual bool DrawModel(void) = 0;

			virtual ~IGLModel(void) {};
	};
}

