#ifndef GLVIDEOSINK_H
#define GLVIDEOSINK_H
#include <GLEngine/Device.h>
#include <GLEngine/Model/Vertex.h>
#include <Multimedia/Filter/BaseFilter/Callback/ABaseVideoCallbackSinkFilter.h>
#include <Utilities/AutoLock/LockObject.h>

namespace multimedia {

class CGLVideoSinkFilter: public ABaseVideoCallbackSinkFilter {
private:
	gint _frameRate;
	gint _frameWidth;
	gint _frameHeight;
	GLenum _glColor;
	GLenum _pixelType;

	gl::Vertex _lowLeft;
	gl::Vertex _lowRight;
	gl::Vertex _topRight;
	gl::Vertex _topLeft;

	utils::LLockObject _lockObject;

	utils::SharedPtr<gl::Device> _glDevice;
	utils::SharedPtr<gl::IModel> _videoFrameGLModel;

public:
	static const float CONST_GL_FRAME_HEIGHT;
	static const float CONST_GL_FRAME_WIDTH;
	static const GLuint CONST_INVALID_TEXTURE_ID;
	static const GLuint CONST_VALID_TEXTURE_ID;
	static const unsigned int CONST_VIDEOFRAME_GLMODEL_ID;

protected:
	virtual bool onRecieveBuffer(GstBaseSink* sink, GstBuffer* gstBuffer);
	virtual bool onSetCaps(GstPad * pad, GstCaps * caps);

public:
	CGLVideoSinkFilter(const utils::SharedPtr<gl::Device>& glDevice)
			throw (GstException);
	virtual ~CGLVideoSinkFilter(void);
};

}

#endif // GLVIDEOSINK_H
