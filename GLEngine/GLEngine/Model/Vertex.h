#pragma once

namespace gl {
	class Vertex {
		private:
			float _posX;
			float _posY;
			float _posZ;

		public:
			Vertex(void);
			Vertex(float posX, float posY, float posZ);
			float getPosX(void) const;
			float getPosY(void) const;
			float getPosZ(void) const;
			void setPosX(float posX);
			void setPosY(float posY);
			void setPosZ(float posZ);
			~Vertex(void);
	};
}

