/*
 * Model_OBJ.cpp
 *
 *  Created on: May 15, 2011
 *      Author: m1cRo
 */

#include "GLWaveFrontObjModel.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <sstream>
#include <stdio.h>
#include <Utilities/AutoLock/AutoLock.h>
#include <Utilities/StrUtil/StrUtil.h>

using namespace std;

const unsigned int GLWaveFrontObjModel::CONST_POINTS_PER_VERTEX=3;
const unsigned int GLWaveFrontObjModel::CONST_TOTAL_FLOATS_IN_TRIANGLE=9;

GLWaveFrontObjModel::GLWaveFrontObjModel(std::istream& modelStream)throw(gl::GLException){
	if(!modelStream.good() || modelStream.eof()){
		throw gl::GLException("ObjModel::ObjModel - Wrong argument data is empty");
	}

	string line;
	int triangleIndex = 0;												// Set triangle index to zero
	while (! modelStream.eof() ){											// Start reading file data
		getline (modelStream,line);											// Get line from file
		if (line.c_str()[0] == 'v'){									// The first character is a v: on this line is a vertex stored.
			line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf
			float posX=0;
			float posY=0;
			float posZ=0;

			std::vector<std::string> tokens = utils::StrUtil::parse(line," ");
			sscanf(line.c_str(),"%f %f %f ",&posX,&posY,&posZ);
			_vertexBuffer.push_back(posX);
			_vertexBuffer.push_back(posY);
			_vertexBuffer.push_back(posZ);
		}


		if (line.c_str()[0] == 'f'){									// The first character is an 'f': on this line is a point stored
		   	line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf

			int vertexNumber[4] = { 0, 0, 0 };
            sscanf(line.c_str(),"%i%i%i",&vertexNumber[0],&vertexNumber[1],	&vertexNumber[2] );
			vertexNumber[0] -= 1;										// OBJ file starts counting from 1
			vertexNumber[1] -= 1;										// OBJ file starts counting from 1
			vertexNumber[2] -= 1;										// OBJ file starts counting from 1

			/********************************************************************
			 * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z).
			 * The vertexBuffer contains all vertexes
			 * The triangles will be created using the vertexes we read previously
			 */
			int tCounter = 0;
			for (unsigned int i = 0; i < CONST_POINTS_PER_VERTEX; i++){
				_triangleFaces.push_back( _vertexBuffer[3*vertexNumber[i] ] );
				_triangleFaces.push_back( _vertexBuffer[3*vertexNumber[i]+1 ] );
				_triangleFaces.push_back( _vertexBuffer[3*vertexNumber[i]+2 ] );
				tCounter += CONST_POINTS_PER_VERTEX;
			}

			/*********************************************************************
			 * Calculate all normals, used for lighting
			 */
			float coord1[3] = { _triangleFaces[triangleIndex], _triangleFaces[triangleIndex+1],_triangleFaces[triangleIndex+2]};
			float coord2[3] = {_triangleFaces[triangleIndex+3],_triangleFaces[triangleIndex+4],_triangleFaces[triangleIndex+5]};
			float coord3[3] = {_triangleFaces[triangleIndex+6],_triangleFaces[triangleIndex+7],_triangleFaces[triangleIndex+8]};

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
			val = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );

			float norm[3];
			norm[0] = vr[0]/val;
			norm[1] = vr[1]/val;
			norm[2] = vr[2]/val;

			tCounter = 0;
			for (unsigned int i = 0; i < CONST_POINTS_PER_VERTEX; i++){
				_normals.push_back( norm[0] );
				_normals.push_back( norm[1] );
				_normals.push_back( norm[2] );
				tCounter += CONST_POINTS_PER_VERTEX;
			}

			triangleIndex += CONST_TOTAL_FLOATS_IN_TRIANGLE;
		}
	}
}


GLWaveFrontObjModel::~GLWaveFrontObjModel(){
}


bool GLWaveFrontObjModel::drawModel(){
	glPushMatrix();
	std::map<unsigned int, Rotation>::iterator currentRotation;
	for(currentRotation=_rotations.begin(); currentRotation!=_rotations.end(); currentRotation++){
		glRotatef(currentRotation->second.getAngle(), currentRotation->second.getAxisX(), currentRotation->second.getAxisY(), currentRotation->second.getAxisZ());
	}

 	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
 	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	glVertexPointer(3,GL_FLOAT,	0,&_triangleFaces.at(0));		// Vertex Pointer to triangle array
	glNormalPointer(GL_FLOAT, 0, &_normals.at(0));				// Normal pointer to normal array
	glDrawArrays(GL_TRIANGLES, 0, _triangleFaces.size()/CONST_POINTS_PER_VERTEX);	// Draw the triangles
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
	glPopMatrix();
	return true;
}


bool GLWaveFrontObjModel::addRotationX(unsigned int rotationId, float angle){
	try{
		utils::AutoLock lock(_lockObject);
		_rotations[rotationId]=Rotation(angle,1.0,0.0,0.0);
	}catch(utils::LockException&){
		return false;
	}

	return true;
}


bool GLWaveFrontObjModel::addRotationY(unsigned int rotationId, float angle){
	try{
		utils::AutoLock lock(_lockObject);
		_rotations[rotationId]=Rotation(angle,0.0,1.0,0.0);
	}catch(utils::LockException&){
		return false;
	}

	return true;
}


bool GLWaveFrontObjModel::addRotationZ(unsigned int rotationId, float angle){
	try{
		utils::AutoLock lock(_lockObject);
		_rotations[rotationId]=Rotation(angle,0.0,0.0,1.0);
	}catch(utils::LockException&){
		return false;
	}

	return true;
}


bool GLWaveFrontObjModel::removeAllRotations(){
	try{
		utils::AutoLock lock(_lockObject);
		_rotations.clear();
	}catch(utils::LockException&){
		return false;
	}

	return true;
}
