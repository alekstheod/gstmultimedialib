#include "Device.h"
#include <GLEngine/Model/IModel.h>
#include <GLEngine/Camera/ICamera.h>
#include <GLEngine/Light/ILight.h>
#include <GLEngine/Model/Vertex.h>
#include <GLEngine/Model/Texture.h>

using namespace std;
using namespace utils;

namespace gl{

	const GLuint Device::CONST_INVALID_TEXTURE=0;

	Device::Device(const Device::RECT& windowRect)throw (GLException) {
	    if (windowRect.left >= windowRect.right) {
	        throw GLException("GLDevice::GLDevice - Wrong window rect");
	    }

	    if (windowRect.top >= windowRect.bottom) {
	        throw GLException("GLDevice::GLDevice - Wrong window rect");
	    }

	    glEnable(GL_DEPTH_TEST);
	    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	    glMatrixMode(GL_PROJECTION);
	    glViewport(0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	    glMatrixMode(GL_MODELVIEW);
	}

	Device::~Device(void)throw (){
	}

	bool Device::drawModels(void) {
	    try {
	        AutoLock lock(_lockObject);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        glMatrixMode(GL_MODELVIEW);
	        glLoadIdentity();
	        if(_camera!=NULL){
	        	_camera->applyCamera();
	        }

	        std::map<void*, utils::SmartPtr<ILight> >::iterator curLight;
	        for(curLight=_lights.begin(); curLight!=_lights.end();curLight++){
	        	curLight->second->applyLight();
	        }

	        std::map<void* , utils::SmartPtr<IModel> >::iterator glModel;
	        for (glModel = _glModels.begin(); glModel != _glModels.end(); glModel++) {
	            if (glModel->second->drawModel() == false) {
	                return false;
	            }
	        }

	        glFlush();
	    } catch (const LockException&) {
	        return false;
	    }

	    return true;
	}

	bool Device::addGLModel(const SmartPtr<IModel>& glModel) {
	    try {
	        AutoLock lock(_lockObject);
	        pair<void* , SmartPtr<IModel> > newEntry(glModel.getPtr(), glModel);
	        if (_glModels.insert(newEntry).second == false) {
	            return false;
	        }
	    } catch (const LockException&) {
	        return false;
	    }

	    return true;
	}

	bool Device::removeGLModel(const utils::SmartPtr<IModel>& glModel) {
	    try {
	        utils::AutoLock lock(_lockObject);
	        if (_glModels.find(glModel.getPtr()) == _glModels.end()) {
	            return false;
	        }

	        _glModels.erase(glModel.getPtr());
	    } catch (const utils::LockException&) {
	        return false;
	    }

	    return true;
	}

	bool Device::setPerspective(unsigned int windowWidth, unsigned int windowHeight) {
	    try {
	        AutoLock lock(_lockObject);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(50.0, 1.0, 1.0, 10000.0);
	        glViewport(0, 0, windowWidth, windowHeight);
	        glMatrixMode(GL_MODELVIEW);
	    } catch (const LockException&) {
	        return false;
	    }

	    return true;
	}

	bool Device::setCamera(const utils::SmartPtr<ICamera>& camera){
	    try {
	    	AutoLock lock(_lockObject);
			_camera=camera;
	    } catch (const utils::LockException&) {
	        return false;
	    }

	    return true;
	}

	bool Device::removeLight(const utils::SmartPtr<ILight>& light){
		try{
			utils::AutoLock lock(_lockObject);
			if(_lights.find(light.getPtr())==_lights.end()){
				return false;
			}

			_lights.erase(light.getPtr());
		}catch(const utils::LockException&){
			return false;
		}

		return true;
	}

	bool Device::setLight(const utils::SmartPtr<ILight>& light){
		try{
			utils::AutoLock lock(_lockObject);
			_lights[light.getPtr()]=light;
		}catch(utils::LockException&){
			return false;
		}

		return true;
	}


	bool Device::generateTexture( utils::SmartPtr< Texture >& newTexture ){
		bool result=false;
		GLuint texture = CONST_INVALID_TEXTURE;
		if(_textures.empty()){
			texture=1;
			newTexture.Attach( new Texture(texture) );
			std::pair< GLuint, utils::SmartPtr<Texture> > newEntry(texture, newTexture);
			_textures.insert(newEntry);
		}else{
			typename std::map< GLuint, utils::SmartPtr<Texture> >::iterator curTexture;
			typename std::map< GLuint, utils::SmartPtr<Texture> >::iterator prevTexture;
			for( curTexture = _textures.begin(); curTexture != _textures.end() && texture==CONST_INVALID_TEXTURE; curTexture++){
				if( curTexture != _textures.begin()){
					GLuint lastTexture=prevTexture->first;
					GLuint currentTexture=curTexture->first-1;
					if( lastTexture<currentTexture  ){
						texture = lastTexture+1;
					}
				}

				prevTexture = curTexture;
			}

			if( texture != CONST_INVALID_TEXTURE ){
				newTexture.Attach( new Texture(texture) );
				typename std::pair< GLuint, utils::SmartPtr<Texture> > newEntry(texture, newTexture);
				result=_textures.insert(newEntry).second;
			}else{
				curTexture = ( --_textures.end() );
				texture = curTexture->first+1;
				newTexture=new Texture(texture);
				std::pair< GLuint, utils::SmartPtr<Texture> > newEntry(texture, newTexture);
				result=_textures.insert(newEntry).second;
			}
		}

		return result;
	}


	bool Device::releaseTexture( const utils::SmartPtr< Texture >& texture ){
		bool result=false;
		if( _textures.find( texture->_texture) != _textures.end() ){
			_textures.erase(texture->_texture);
			result=true;
		}

		return result;
	}
}

