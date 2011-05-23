#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <Utilities/SmartPtr/SmartPtr.h>
#include <Utilities/AutoLock/LockObject.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/GLVertex.h>
#include <GLEngine/Model/IGLModel.h>
#include <GLEngine/Camera/IGLCamera.h>
#include <GLEngine/Light/IGLLight.h>

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
			std::map<unsigned int, utils::SmartPtr<IGLLight> > _lights;

		public:
			GLDevice(const GLDevice::RECT&) throw (GLException);
			bool drawModels(void);
			bool setCamera(const utils::SmartPtr<IGLCamera>& camera);
			bool addGLModel(unsigned int,const utils::SmartPtr<IGLModel>& glModel);
			bool removeGLModel(unsigned int glModelId);
			bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
			bool removeLight(unsigned int lightId);
			bool setLight(unsigned int lightId, const utils::SmartPtr<IGLLight>& light);
			virtual ~GLDevice(void) throw ();
	};

}
