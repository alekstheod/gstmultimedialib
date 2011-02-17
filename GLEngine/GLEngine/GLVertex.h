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
			float GetPosX(void) const;
			float GetPosY(void) const;
			float GetPosZ(void) const;
			void SetPosX(float posX);
			void SetPosY(float posY);
			void SetPosZ(float posZ);
			~GLVertex(void);
	};
}

