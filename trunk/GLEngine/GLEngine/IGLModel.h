#pragma once

namespace gl {
	class IGLModel {
		public:

			IGLModel(void) {};
			virtual bool drawModel(void) = 0;
			virtual ~IGLModel(void) {};
	};
}

