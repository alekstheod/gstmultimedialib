/*
 * Model_OBJ.h
 *
 *  Created on: May 15, 2011
 *      Author: m1cRo
 */

#ifndef MODEL_OBJ_H_
#define MODEL_OBJ_H_
#include <vector>
#include <map>
#include <string>
#include <GLEngine/Model/IModel.h>
#include <GLEngine/GLException.h>
#include <Utilities/AutoLock/LockObject.h>
#include <GLEngine/Model/Wavefront/Object.h>

namespace gl {

namespace wavefront {

class Model: public gl::IModel {
private:
	std::map<std::string, Object> _glObjects;
	std::map<unsigned int, Rotation> _rotations;
	utils::LockObject _lockObject;

public:
	Model(std::istream& modelStream) throw (gl::GLException);
	bool drawModel(); // Draws the model on the screen
	bool addRotationX(unsigned int rotationId, float angle);
	bool addRotationY(unsigned int rotationId, float angle);
	bool addRotationZ(unsigned int rotationId, float angle);
	bool removeAllRotations();

	bool addRotationX(const std::string& objectName, unsigned int rotationId,
			float angle);
	bool addRotationY(const std::string& objectName, unsigned int rotationId,
			float angle);
	bool addRotationZ(const std::string& objectName, unsigned int rotationId,
			float angle);
	bool removeAllRotations(const std::string& objectName);

	virtual ~Model();
};

}
}

#endif /* MODEL_OBJ_H_ */
