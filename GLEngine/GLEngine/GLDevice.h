#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <Utilities/SmartPtr/SmartPtr.h>
#include <Utilities/AutoLock/LockObject.h>
#include <GLEngine/GLException.h>
#include <GLEngine/GLVertex.h>
#include <GLEngine/IGLModel.h>
#include <GLEngine/IGLCamera.h>

namespace gl {

	class GLDevice {
		public:
			struct RECT {
					int left;
					int top;
					int right;
					int bottom;
			};

		private:
			utils::LockObject _lockObject;
			bool _isOpenGLInitialized;
			bool _windowWasResized;
			unsigned int _windowWidth;
			unsigned int _windowHeight;
			std::map<unsigned int, utils::SmartPtr<IGLModel> > _glModels;
			utils::SmartPtr<IGLCamera> _camera;

		public:
			GLDevice(const GLDevice::RECT&) throw (GLException);
			bool drawModels(void);
			bool setCamera(const utils::SmartPtr<IGLCamera>& camera);
			bool addGLModel(unsigned int,const utils::SmartPtr<IGLModel>& glModel);
			bool removeGLModel(unsigned int glModelId);
			bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
			virtual ~GLDevice(void) throw ();
	};

}
