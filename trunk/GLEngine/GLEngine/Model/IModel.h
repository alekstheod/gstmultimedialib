#pragma once
#include <string>
#include <GLEngine/Model/Vertex.h>

namespace gl {

	class IModel {
		public:

			IModel(void) {};
			virtual bool drawModel(void) = 0;
			virtual bool addRotationX(unsigned int rotationId, float angle)=0;
			virtual bool addRotationY(unsigned int rotationId, float angle)=0;
			virtual bool addRotationZ(unsigned int rotationId, float angle)=0;
			virtual bool removeAllRotations()=0;
			virtual ~IModel(void) {};
	};

}

