#ifndef GLVIDEOSINK_H
#define GLVIDEOSINK_H
#include <GLEngine/GLDevice.h>
#include <Multimedia/Filter/BaseFilter/Callback/ABaseVideoCallbackSinkFilter.h>
#include <Utilities/AutoLock/LockObject.h>

namespace multimedia{

	class CGLVideoSinkFilter: public ABaseVideoCallbackSinkFilter {
		private:
			gint _frameRate;
			gint _frameWidth;
			gint _frameHeight;
			GLenum _glColor;
			GLenum _pixelType;

			gl::GLVertex _lowLeft;
			gl::GLVertex _lowRight;
			gl::GLVertex _topRight;
			gl::GLVertex _topLeft;
			GLuint _texture;

			utils::LLockObject _lockObject;

			utils::SmartPtr<gl::GLDevice> _glDevice;
			utils::SmartPtr<gl::IGLModel> _videoFrameGLModel;

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
			CGLVideoSinkFilter(const utils::SmartPtr<gl::GLDevice>& glDevice) throw (GstException);
			virtual ~CGLVideoSinkFilter(void);
	};

}

#endif // GLVIDEOSINK_H
