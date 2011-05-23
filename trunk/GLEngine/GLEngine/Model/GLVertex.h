#pragma once

namespace gl {
	class GLVertex {
		private:
			float _posX;
			float _posY;
			float _posZ;

		public:
			GLVertex(void);
			GLVertex(float posX, float posY, float posZ);
			float getPosX(void) const;
			float getPosY(void) const;
			float getPosZ(void) const;
			void setPosX(float posX);
			void setPosY(float posY);
			void setPosZ(float posZ);
			~GLVertex(void);
	};
}

