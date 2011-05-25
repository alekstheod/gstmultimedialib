#pragma once
#include <string>

namespace gl {
	class IGLModel {
		public:

			IGLModel(void) {};
			virtual bool drawModel(void) = 0;
			virtual bool addRotationX(unsigned int rotationId, float angle)=0;
			virtual bool addRotationY(unsigned int rotationId, float angle)=0;
			virtual bool addRotationZ(unsigned int rotationId, float angle)=0;
			virtual bool removeAllRotations()=0;

			virtual bool addRotationX(const std::string& objectName, unsigned int rotationId, float angle)=0;
			virtual bool addRotationY(const std::string& objectName, unsigned int rotationId, float angle)=0;
			virtual bool addRotationZ(const std::string& objectName, unsigned int rotationId, float angle)=0;
			virtual bool removeAllRotations(const std::string& objectName)=0;

			virtual ~IGLModel(void) {};
	};
}

