/*
 * GLObject.cpp
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#include "GLObject.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <Utilities/StrUtil/StrUtil.h>
#include <Utilities/AutoLock/AutoLock.h>
#include <algorithm>
#include <math.h>

namespace gl {

	namespace wavefront {

		const unsigned int GLObject::CONST_POINTS_PER_VERTEX = 3;
		const unsigned int GLObject::CONST_TOTAL_FLOATS_IN_TRIANGLE = 9;
		const std::string GLObject::CONST_FACES_TOKEN="f";
		const std::string GLObject::CONST_VERTEX_NORMALS_TOKEN="vn";
		const std::string GLObject::CONST_VERTECES_TOKEN="v";
		const std::string GLObject::CONST_OBJECT_TOKEN="o";
		const std::string GLObject::CONST_GROUP_TOKEN="g";

		GLObject::GLObject(std::istream& modelStream, unsigned int previewMaxFacesIndex)throw(gl::GLException){
			if(!modelStream.good() || modelStream.eof()){
				throw gl::GLException("ObjModel::ObjModel - Wrong argument data is empty");
			}

			std::string line;
			int triangleIndex = 0;
			std::vector<std::string> tokens;
			do{ // Start reading file data
				getline(modelStream, line); // Get line from file
				tokens = utils::StrUtil::parse(line, " ");
				if (tokens[0] == CONST_VERTECES_TOKEN) { // The first character is a v: on this line is a vertex stored.
					if (tokens.size() != 5) {
						throw gl::GLException("ObjModel::ObjModel - Wrong stream format");
					}

					try {
						_vertexBuffer.push_back(utils::StrUtil::lexical_cast<float>(tokens[1]));
						_vertexBuffer.push_back(utils::StrUtil::lexical_cast<float>(tokens[2]));
						_vertexBuffer.push_back(utils::StrUtil::lexical_cast<float>(tokens[3]));
					} catch (const utils::bad_cast&) {
						throw gl::GLException("ObjModel::ObjModel - Wrong stream format");
					}
				}else if (tokens[0] == CONST_FACES_TOKEN) { // The first character is an 'f': on this line is a point stored
					unsigned int vertexNumber[4] = { 0, 0, 0 };
					if (tokens.size() != 5) {
						throw gl::GLException("ObjModel::ObjModel - Wrong stream format");
					}

					try {
						vertexNumber[0] = utils::StrUtil::lexical_cast<unsigned int>(tokens[1]);
						vertexNumber[1] = utils::StrUtil::lexical_cast<unsigned int>(tokens[2]);
						vertexNumber[2] = utils::StrUtil::lexical_cast<unsigned int>(tokens[3]);
						_vertexNumbers.push_back(vertexNumber[0]);
						_vertexNumbers.push_back(vertexNumber[1]);
						_vertexNumbers.push_back(vertexNumber[2]);

						vertexNumber[0] -= (1+previewMaxFacesIndex); // OBJ file starts counting from 1
						vertexNumber[1] -= (1+previewMaxFacesIndex); // OBJ file starts counting from 1
						vertexNumber[2] -= (1+previewMaxFacesIndex);
					} catch (const utils::bad_cast&) {
						throw gl::GLException("ObjModel::ObjModel - Wrong stream format");
					}

					/********************************************************************
					 * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z).
					 * The vertexBuffer contains all vertexes
					 * The triangles will be created using the vertexes we read previously
					 */
					int tCounter = 0;
					for (unsigned int i = 0; i < CONST_POINTS_PER_VERTEX; i++) {
						_triangleFaces.push_back(_vertexBuffer[3 * vertexNumber[i]]);
						_triangleFaces.push_back(_vertexBuffer[3 * vertexNumber[i] + 1]);
						_triangleFaces.push_back(_vertexBuffer[3 * vertexNumber[i] + 2]);
						tCounter += CONST_POINTS_PER_VERTEX;
					}

					/*********************************************************************
					 * Calculate all normals, used for lighting
					 */
					float coord1[3] = { _triangleFaces[triangleIndex], _triangleFaces[triangleIndex + 1], _triangleFaces[triangleIndex + 2] };
					float coord2[3] = { _triangleFaces[triangleIndex + 3], _triangleFaces[triangleIndex + 4], _triangleFaces[triangleIndex + 5] };
					float coord3[3] = { _triangleFaces[triangleIndex + 6], _triangleFaces[triangleIndex + 7], _triangleFaces[triangleIndex + 8] };

					/* calculate Vector1 and Vector2 */
					float va[3], vb[3], vr[3], val;
					va[0] = coord1[0] - coord2[0];
					va[1] = coord1[1] - coord2[1];
					va[2] = coord1[2] - coord2[2];

					vb[0] = coord1[0] - coord3[0];
					vb[1] = coord1[1] - coord3[1];
					vb[2] = coord1[2] - coord3[2];

					/* cross product */
					vr[0] = va[1] * vb[2] - vb[1] * va[2];
					vr[1] = vb[0] * va[2] - va[0] * vb[2];
					vr[2] = va[0] * vb[1] - vb[0] * va[1];

					/* normalization factor */
					val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

					float norm[3];
					norm[0] = vr[0] / val;
					norm[1] = vr[1] / val;
					norm[2] = vr[2] / val;

					tCounter = 0;
					for (unsigned int i = 0; i < CONST_POINTS_PER_VERTEX; i++) {
						_normals.push_back(norm[0]);
						_normals.push_back(norm[1]);
						_normals.push_back(norm[2]);
						tCounter += CONST_POINTS_PER_VERTEX;
					}

					triangleIndex += CONST_TOTAL_FLOATS_IN_TRIANGLE;
				}else if(tokens[0]=="usemtl"){
					if(tokens.size()!=3){
						throw gl::GLException("ObjModel::ObjModel - Wrong stream format");
					}

					_material=tokens[1];
				}else if(tokens[0]=="mtllib"){
					if(tokens.size()!=3){
						throw gl::GLException("ObjModel::ObjModel - Wrong stream format");
					}

					_material=tokens[1];
				}
			}while(!modelStream.eof() && tokens[0]!=CONST_OBJECT_TOKEN && tokens[0]!=CONST_GROUP_TOKEN);

			if(tokens[0]==CONST_OBJECT_TOKEN || tokens[0]==CONST_GROUP_TOKEN){
				modelStream.seekg(-line.length()-1, std::ios::cur);
			}
		}

		GLObject::~GLObject() {
			// TODO Auto-generated destructor stub
		}

		bool GLObject::addRotationX(unsigned int rotationId, float angle){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations[rotationId]=Rotation(angle,1.0,0.0,0.0);
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}

		bool GLObject::addRotationY(unsigned int rotationId, float angle){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations[rotationId]=Rotation(angle,0.0,1.0,0.0);
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}

		bool GLObject::addRotationZ(unsigned int rotationId, float angle){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations[rotationId]=Rotation(angle,0.0,0.0,1.0);
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}

		bool GLObject::removeAllRotations(){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations.clear();
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}

		bool GLObject::drawObject(){
			bool result=true;
		 	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
		 	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
			glPushMatrix();
			try{
				utils::AutoLock lock(_lockObject);
				std::map<unsigned int, Rotation>::iterator currentRotation;
				for(currentRotation=_rotations.begin(); currentRotation!=_rotations.end(); currentRotation++){
					glRotatef(currentRotation->second.getAngle(), currentRotation->second.getAxisX(), currentRotation->second.getAxisY(), currentRotation->second.getAxisZ());
				}

			}catch(const utils::LockException&){
				result=false;
			}

			glVertexPointer( 3, GL_FLOAT, 0, &_triangleFaces.at(0) );		// Vertex Pointer to triangle array
			glNormalPointer( GL_FLOAT, 0, &_normals.at(0) );				// Normal pointer to normal array
			glDrawArrays( GL_TRIANGLES, 0, _triangleFaces.size()/CONST_POINTS_PER_VERTEX );	// Draw the triangles

			glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
			glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
			glPopMatrix();
			return result;
		}

		unsigned int GLObject::getLastVertexNumber(){
			unsigned int result=0;
			try{
				utils::AutoLock lock(_lockObject);
				std::vector<unsigned int>::iterator res=std::max_element(_vertexNumbers.begin(), _vertexNumbers.end());
				if(res!=_vertexNumbers.end()){
					result=*res;
				}
			}catch(const utils::LockException&){
				result=0;
			}

			return result;
		}

	}

}
