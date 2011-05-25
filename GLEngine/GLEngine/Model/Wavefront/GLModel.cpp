/*
 * Model_OBJ.cpp
 *
 *  Created on: May 15, 2011
 *      Author: m1cRo
 */

#include "GLModel.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Utilities/AutoLock/AutoLock.h>
#include <Utilities/StrUtil/StrUtil.h>

using namespace std;

namespace gl{

	namespace wavefront{


		GLModel::GLModel(std::istream& modelStream)throw(gl::GLException){
			if(!modelStream.good() || modelStream.eof()){
				throw gl::GLException("ObjModel::ObjModel - Wrong argument data is empty");
			}

			unsigned int previewMaxFacesIndex=0;
			std::string line;
			while(!modelStream.eof()){
				getline(modelStream, line);
				std::vector<std::string> tokens=utils::StrUtil::parse(line, " ");
				if(tokens[0]=="o" || tokens[0]=="g"){
					if(tokens.size()!=3){
						throw GLException("GLModel::GLModel - Illegal modelStream");
					}

					GLObject obj(modelStream,previewMaxFacesIndex);
					previewMaxFacesIndex=obj.getLastVertexNumber();
					std::pair< std::string, GLObject > newEntry(tokens[1], obj);
					if(!_glObjects.insert(newEntry).second){
						throw GLException("GLModel::GLModel - Illegal modelStream");
					}
				}
			}
		}


		GLModel::~GLModel(){
		}


		bool GLModel::drawModel(){
			glPushMatrix();
		 	std::map< unsigned int, Rotation>::iterator curRotation;
		 	for(curRotation=_rotations.begin(); curRotation!=_rotations.end();curRotation++){
		 		glRotatef(curRotation->second.getAngle(), curRotation->second.getAxisX(), curRotation->second.getAxisY(), curRotation->second.getAxisZ());
		 	}

		 	std::map< std::string, GLObject>::iterator curObject;
		 	for(curObject=_glObjects.begin();curObject!=_glObjects.end();curObject++){
		 		curObject->second.drawObject();
		 	}

			glPopMatrix();
			return true;
		}


		bool GLModel::addRotationX(unsigned int rotationId, float angle){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations[rotationId]=Rotation(angle,1.0,0.0,0.0);
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}


		bool GLModel::addRotationY(unsigned int rotationId, float angle){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations[rotationId]=Rotation(angle,0.0,1.0,0.0);
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}


		bool GLModel::addRotationZ(unsigned int rotationId, float angle){
			try{
				utils::AutoLock lock(_lockObject);
				_rotations[rotationId]=Rotation(angle,0.0,0.0,1.0);
			}catch(utils::LockException&){
				return false;
			}

			return true;
		}


		bool GLModel::removeAllRotations(){
			bool result=true;
			try{
				utils::AutoLock lock(_lockObject);
				_rotations.clear();
			}catch(utils::LockException&){
				return false;
			}

			return result;
		}

		bool GLModel::addRotationX(const std::string& objectName, unsigned int rotationId, float angle){
			bool result=true;
			try{
				utils::AutoLock lock(_lockObject);
				std::map< std::string, GLObject>::iterator currentObject=_glObjects.find(objectName);
				if(currentObject!=_glObjects.end()){
					result=currentObject->second.addRotationX(rotationId, angle);
				}
			}catch(utils::LockException&){
				return false;
			}

			return result;
		}


		bool GLModel::addRotationY(const std::string& objectName, unsigned int rotationId, float angle){
			bool result=true;
			try{
				utils::AutoLock lock(_lockObject);
				std::map< std::string, GLObject>::iterator currentObject=_glObjects.find(objectName);
				if(currentObject!=_glObjects.end()){
					result=currentObject->second.addRotationY(rotationId, angle);
				}
			}catch(utils::LockException&){
				return false;
			}

			return result;
		}


		bool GLModel::addRotationZ(const std::string& objectName, unsigned int rotationId, float angle){
			bool result=true;
			try{
				utils::AutoLock lock(_lockObject);
				std::map< std::string, GLObject>::iterator currentObject=_glObjects.find(objectName);
				if(currentObject!=_glObjects.end()){
					result=currentObject->second.addRotationZ(rotationId, angle);
				}
			}catch(utils::LockException&){
				return false;
			}

			return result;
		}


		bool GLModel::removeAllRotations(const std::string& objectName){
			bool result=true;
			try{
				utils::AutoLock lock(_lockObject);
				std::map< std::string, GLObject>::iterator currentObject=_glObjects.find(objectName);
				if(currentObject!=_glObjects.end()){
					result=currentObject->second.removeAllRotations();
				}
			}catch(utils::LockException&){
				return false;
			}

			return result;
		}
	}

}

