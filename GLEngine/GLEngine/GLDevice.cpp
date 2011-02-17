#include "GLDevice.h"

using namespace std;
using namespace utils;

namespace gl{

	const GLVertex GLDevice::CONST_DEFAULT_CAMERA_POSITION = GLVertex(0.0f, 0.0f, 1.41f);
	const GLVertex GLDevice::CONST_DEFAULT_LOOKAT_POSITION = GLVertex(0.0f, 0.0f, 0.0f);

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

	GLDevice::~GLDevice(void)throw () {
	}

	bool GLDevice::DrawModels(void) {
	    try {
	        AutoLock lock(_lockObject);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        glLoadIdentity();
	        std::map<unsigned int, utils::SmartPtr<IGLModel> >::iterator glModel;
	        for (glModel = _glModels.begin(); glModel != _glModels.end(); glModel++) {
	            if (glModel->second->DrawModel() == false) {
	                return false;
	            }
	        }
	        glFlush();
	    } catch (const LockException&) {
	        return false;
	    }
	    return true;
	}

	bool GLDevice::AddGLModel(unsigned int glModelId, const SmartPtr<IGLModel>& glModel) {
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

	bool GLDevice::RemoveGLModel(unsigned int glModelId) {
	    try {
	        utils::AutoLock lock(_lockObject);
	        if (_glModels.find(glModelId) == _glModels.end()) {
	            return false;
	        }

	        _glModels.erase(glModelId);
	        return true;
	    } catch (const utils::LockException&) {
	        return false;
	    }
	    return true;
	}

	bool GLDevice::SetPerspective(unsigned int windowWidth, unsigned int windowHeight) {
	    try {
	        AutoLock lock(_lockObject);
	        glLoadIdentity();
	        glViewport(0, 0, windowWidth, windowHeight);
	        glMatrixMode(GL_MODELVIEW);

	    } catch (const LockException&) {
	        return false;
	    }
	    return true;
	}

}

