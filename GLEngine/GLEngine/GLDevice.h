#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <list>
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

		public:
			static const GLuint CONST_INVALID_TEXTURE;

		private:
			utils::LockObject _lockObject;
			bool _isOpenGLInitialized;
			bool _windowWasResized;
			unsigned int _windowWidth;
			unsigned int _windowHeight;
			std::map<void* , utils::SmartPtr<IGLModel> > _glModels;
			utils::SmartPtr<IGLCamera> _camera;
			std::map<void* , utils::SmartPtr<IGLLight> > _lights;
			std::list< GLuint > _textures;

		public:
			GLDevice(const GLDevice::RECT&) throw (GLException);
			bool drawModels(void);
			bool setCamera(const utils::SmartPtr<IGLCamera>& camera);
			bool addGLModel(const utils::SmartPtr<IGLModel>& glModel);
			bool removeGLModel(const utils::SmartPtr<IGLModel>& glModel);
			bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
			bool removeLight(const utils::SmartPtr<IGLLight>& light);
			bool setLight(const utils::SmartPtr<IGLLight>& light);
			bool generateTexture( const GLsizei namesNumber, GLuint& texture);
			bool releaseTexture( const GLuint texture);
			virtual ~GLDevice(void) throw ();
	};

}
