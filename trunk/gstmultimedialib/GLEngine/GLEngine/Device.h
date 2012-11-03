#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <Utilities/SmartPtr/SharedPtr.h>
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
	std::map<void*, utils::SharedPtr<IModel> > _glModels;
	utils::SharedPtr<ICamera> _camera;
	std::map<void*, utils::SharedPtr<ILight> > _lights;
	std::map<GLuint, utils::SharedPtr<Texture> > _textures;

public:
	Device(const Device::RECT&) throw (GLException);
	bool drawModels(void);
	bool setCamera(const utils::SharedPtr<ICamera>& camera);
	bool addGLModel(const utils::SharedPtr<IModel>& glModel);
	bool removeGLModel(const utils::SharedPtr<IModel>& glModel);
	bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
	bool removeLight(const utils::SharedPtr<ILight>& light);
	bool setLight(const utils::SharedPtr<ILight>& light);
	bool generateTexture(utils::SharedPtr<Texture>& newTexture);
	bool releaseTexture(const utils::SharedPtr<Texture>& texture);
	virtual ~Device(void) throw ();
};

}