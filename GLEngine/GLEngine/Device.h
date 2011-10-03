#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <Utilities/SmartPtr/SmartPtr.h>
#include <Utilities/AutoLock/LockObject.h>
#include <GLEngine/GLException.h>

namespace gl {

	class ICamera;
	class IModel;
	class ILight;
	class Texture;

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
			std::map< GLuint, utils::SmartPtr< Texture > > _textures;

		public:
			Device(const Device::RECT&) throw (GLException);
			bool drawModels(void);
			bool setCamera(const utils::SmartPtr<ICamera>& camera);
			bool addGLModel(const utils::SmartPtr<IModel>& glModel);
			bool removeGLModel(const utils::SmartPtr<IModel>& glModel);
			bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
			bool removeLight(const utils::SmartPtr<ILight>& light);
			bool setLight(const utils::SmartPtr<ILight>& light);
			bool generateTexture( utils::SmartPtr< Texture >& newTexture );
			bool releaseTexture( const utils::SmartPtr< Texture >& texture);
			virtual ~Device(void) throw ();
	};

}
