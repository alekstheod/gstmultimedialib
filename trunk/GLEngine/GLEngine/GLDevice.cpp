#include "GLDevice.h"

using namespace std;
using namespace utils;

namespace gl{

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

	        std::map<unsigned int, utils::SmartPtr<IGLLight> >::iterator curLight;
	        for(curLight=_lights.begin(); curLight!=_lights.end();curLight++){
	        	curLight->second->applyLight();
	        }

	        std::map<unsigned int, utils::SmartPtr<IGLModel> >::iterator glModel;
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

	bool GLDevice::addGLModel(unsigned int glModelId, const SmartPtr<IGLModel>& glModel) {
	    try {
	        AutoLock lock(_lockObject);
	        pair<unsigned int, SmartPtr<IGLModel> > newEntry(glModelId, glModel);
	        if (_glModels.insert(newEntry).second == false) {
	            return false;
	        }
	    } catch (const LockException&) {
	        return false;
	    }

	    return true;
	}

	bool GLDevice::removeGLModel(unsigned int glModelId) {
	    try {
	        utils::AutoLock lock(_lockObject);
	        if (_glModels.find(glModelId) == _glModels.end()) {
	            return false;
	        }

	        _glModels.erase(glModelId);
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

	bool GLDevice::removeLight(unsigned int lightId){
		try{
			utils::AutoLock lock(_lockObject);
			if(_lights.find(lightId)==_lights.end()){
				return false;
			}

			_lights.erase(lightId);
		}catch(const utils::LockException&){
			return false;
		}

		return true;
	}

	bool GLDevice::setLight(unsigned int lightId, const utils::SmartPtr<IGLLight>& light){
		try{
			utils::AutoLock lock(_lockObject);
			_lights[lightId]=light;
		}catch(utils::LockException&){
			return false;
		}

		return true;
	}
}

