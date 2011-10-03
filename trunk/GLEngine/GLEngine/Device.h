#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <list>
#include <Utilities/SmartPtr/SmartPtr.h>
#include <Utilities/AutoLock/LockObject.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/Vertex.h>
#include <GLEngine/Model/IModel.h>
#include <GLEngine/Camera/ICamera.h>
#include <GLEngine/Light/ILight.h>

namespace gl {

	class Device {
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
			std::map<void* , utils::SmartPtr<IModel> > _glModels;
			utils::SmartPtr<ICamera> _camera;
			std::map<void* , utils::SmartPtr<ILight> > _lights;
			std::list< GLuint > _textures;

		public:
			Device(const Device::RECT&) throw (GLException);
			bool drawModels(void);
			bool setCamera(const utils::SmartPtr<ICamera>& camera);
			bool addGLModel(const utils::SmartPtr<IModel>& glModel);
			bool removeGLModel(const utils::SmartPtr<IModel>& glModel);
			bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
			bool removeLight(const utils::SmartPtr<ILight>& light);
			bool setLight(const utils::SmartPtr<ILight>& light);
			bool generateTexture( const GLsizei namesNumber, GLuint& texture);
			bool releaseTexture( const GLuint texture);
			virtual ~Device(void) throw ();
	};

}
