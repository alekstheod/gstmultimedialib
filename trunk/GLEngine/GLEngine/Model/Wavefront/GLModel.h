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
#include <GLEngine/Model/IGLModel.h>
#include <GLEngine/GLException.h>
#include <Utilities/AutoLock/LockObject.h>

namespace gl{

	namespace wavefront{

		class GLModel : public gl::IGLModel {
			class Rotation{
				private:
					float _angle;
					float _xAxis;
					float _yAxis;
					float _zAxis;

				public:
					Rotation(){
						_angle=0;
						_xAxis=0;
						_yAxis=0;
						_zAxis=0;
					}

					Rotation(float angle, float xAxis, float yAxis, float zAxis){
						_angle=angle;
						_xAxis=xAxis;
						_yAxis=yAxis;
						_zAxis=zAxis;
					}

					float getAngle(){return _angle;}
					float getAxisX(){return _xAxis;}
					float getAxisY(){return _yAxis;}
					float getAxisZ(){return _zAxis;}
					~Rotation(){};
			};

			public:
				static const unsigned int CONST_POINTS_PER_VERTEX;
				static const unsigned int CONST_TOTAL_FLOATS_IN_TRIANGLE;

			private:
				std::map<unsigned int, Rotation> _rotations;
				std::vector<float> _normals; // Stores the normals
				std::vector<float> _triangleFaces; // Stores the triangles
				std::vector<float> _vertexBuffer; // Stores the points which make the object
				utils::LockObject _lockObject;

			public:
				GLModel(std::istream& modelStream)throw(gl::GLException);
				bool drawModel(); // Draws the model on the screen
				bool addRotationX(unsigned int rotationId, float angle);
				bool addRotationY(unsigned int rotationId, float angle);
				bool addRotationZ(unsigned int rotationId, float angle);
				bool removeAllRotations();
				virtual ~GLModel();
		};


	}
}

#endif /* MODEL_OBJ_H_ */
