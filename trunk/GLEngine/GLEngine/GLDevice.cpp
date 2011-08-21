#include "GLDevice.h"

using namespace std;
using namespace utils;

namespace gl{

	const GLuint GLDevice::CONST_INVALID_TEXTURE=0;

	GLDevice::GLDevice(const GLDevice::RECT& windowRect)throw (GLException) {
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

	GLDevice::~GLDevice(void)throw (){
	}

	bool GLDevice::drawModels(void) {
	    try {
	        AutoLock lock(_lockObject);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        glMatrixMode(GL_MODELVIEW);
	        glLoadIdentity();
	        if(_camera!=NULL){
	        	_camera->applyCamera();
	        }

	        std::map<void*, utils::SmartPtr<IGLLight> >::iterator curLight;
	        for(curLight=_lights.begin(); curLight!=_lights.end();curLight++){
	        	curLight->second->applyLight();
	        }

	        std::map<void* , utils::SmartPtr<IGLModel> >::iterator glModel;
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

	bool GLDevice::addGLModel(const SmartPtr<IGLModel>& glModel) {
	    try {
	        AutoLock lock(_lockObject);
	        pair<void* , SmartPtr<IGLModel> > newEntry(glModel.getPtr(), glModel);
	        if (_glModels.insert(newEntry).second == false) {
	            return false;
	        }
	    } catch (const LockException&) {
	        return false;
	    }

	    return true;
	}

	bool GLDevice::removeGLModel(const utils::SmartPtr<IGLModel>& glModel) {
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

	bool GLDevice::setPerspective(unsigned int windowWidth, unsigned int windowHeight) {
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

	bool GLDevice::setCamera(const utils::SmartPtr<IGLCamera>& camera){
	    try {
	    	AutoLock lock(_lockObject);
			_camera=camera;
	    } catch (const utils::LockException&) {
	        return false;
	    }

	    return true;
	}

	bool GLDevice::removeLight(const utils::SmartPtr<IGLLight>& light){
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

	bool GLDevice::setLight(const utils::SmartPtr<IGLLight>& light){
		try{
			utils::AutoLock lock(_lockObject);
			_lights[light.getPtr()]=light;
		}catch(utils::LockException&){
			return false;
		}

		return true;
	}


	bool GLDevice::generateTexture( const GLsizei namesNumber, GLuint& texture ){
		texture = CONST_INVALID_TEXTURE;
		if(_textures.empty()){
			texture=1;
			_textures.push_back(texture);
			glGenTextures(namesNumber, &texture);
		}else{
			std::list< GLuint >::iterator curTexture;
			std::list< GLuint >::iterator prevTexture;
			for( curTexture = _textures.begin(); curTexture != _textures.end(); curTexture++){
				if( curTexture != _textures.begin()){
					if( *prevTexture < (*curTexture)-1 ){
						texture = (*prevTexture) + 1;
					}
				}

				prevTexture = curTexture;
			}

			if(texture != CONST_INVALID_TEXTURE){
				_textures.push_back(texture);
			}else{
				curTexture = (--_textures.end());
				texture = (*curTexture)+1;
				_textures.push_back(texture);
			}

			glGenTextures(namesNumber, &texture);
		}

		_textures.sort();
		return true;
	}


	bool GLDevice::releaseTexture( const GLuint texture ){
		std::list< GLuint >::iterator curTexture=_textures.begin();
		while( curTexture != _textures.end() && *curTexture != texture){
			curTexture++;
		}

		if( curTexture == _textures.end() ){
			return false;
		}

		_textures.erase(curTexture);
		glDeleteTextures(1, &texture);
		return true;
	}
}

