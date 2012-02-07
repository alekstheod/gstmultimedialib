/*
 * GLObject.h
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_
#include <vector>
#include <map>
#include <string>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/Rotation.h>
#include <Utilities/AutoLock/LockObject.h>
#include <sstream>

namespace gl {

namespace wavefront {

class Object {
public:
	static const unsigned int CONST_POINTS_PER_VERTEX;
	static const unsigned int CONST_TOTAL_FLOATS_IN_TRIANGLE;
	static const std::string CONST_FACES_TOKEN;
	static const std::string CONST_VERTEX_NORMALS_TOKEN;
	static const std::string CONST_VERTECES_TOKEN;
	static const std::string CONST_OBJECT_TOKEN;
	static const std::string CONST_GROUP_TOKEN;

private:
	std::vector<float> _normals; // Stores the normals
	std::vector<float> _triangleFaces; // Stores the triangles
	std::vector<unsigned int> _vertexNumbers;
	std::vector<float> _vertexBuffer; // Stores the points which make the object
	std::map<unsigned int, Rotation> _rotations;
	std::string _material;
	std::string _mglLib;
	utils::LockObject _lockObject;

public:
	Object(std::istream& modelStream, unsigned int previewMaxFacesIndex)
			throw (gl::GLException);
	bool drawObject();
	bool addRotationX(unsigned int rotationId, float angle);
	bool addRotationY(unsigned int rotationId, float angle);
	bool addRotationZ(unsigned int rotationId, float angle);
	bool removeAllRotations();
	unsigned int getLastVertexNumber();
	virtual ~Object();
};

}

}

#endif /* GLOBJECT_H_ */
