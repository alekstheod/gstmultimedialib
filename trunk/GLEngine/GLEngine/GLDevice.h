#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <Utilities/SmartPtr/SmartPtr.h>
#include <Utilities/AutoLock/LockObject.h>
#include "GLException.h"
#include "GLVertex.h"
#include "IGLModel.h"

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

		public:
			static const GLVertex CONST_DEFAULT_CAMERA_POSITION;
			static const GLVertex CONST_DEFAULT_LOOKAT_POSITION;

		public:
			GLDevice(const GLDevice::RECT&) throw (GLException);
			bool drawModels(void);
			bool addGLModel(unsigned int,const utils::SmartPtr<IGLModel>& glModel);
			bool removeGLModel(unsigned int glModelId);
			bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
			virtual ~GLDevice(void) throw ();
	};

}
