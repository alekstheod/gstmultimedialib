#ifndef GLVIDEOSINK_H
#define GLVIDEOSINK_H
#include <GLEngine/GLDevice.h>
#include <Multimedia/Filter/BaseFilter/ABaseCallbackSink.h>
#include <Utilities/Strategy/Strategy.h>
#include <Utilities/AutoLock/LockObject.h>

namespace multimedia{

	class CGLVideoSink: public ABaseCallbackSink {
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

			utils::LLockObject _lockObject;

			utils::SmartPtr<gl::GLDevice> _glDevice;
			utils::SmartPtr<gl::IGLModel> _videoFrameGLModel;

		public:
			class IGLVideoSinkStrategy {
				public:
					IGLVideoSinkStrategy() {};
					virtual void OnSetCaps(GstCaps* caps) = 0;
					virtual void OnReceiveBuffer(GstBuffer* buffer) = 0;

					virtual ~IGLVideoSinkStrategy() {};
			};

		private:
			utils::Strategy<IGLVideoSinkStrategy> _strategy;

		public:
			static const float CONST_GL_FRAME_HEIGHT;
			static const float CONST_GL_FRAME_WIDTH;

		protected:
			virtual bool OnRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer);
			virtual bool OnSetCaps(GstPad * pad, GstCaps * caps);

		public:
			CGLVideoSink(const utils::SmartPtr<gl::GLDevice>& glDevice) throw (GstException);
			bool RegisterGLVideoSinkStrategy(const utils::SmartPtr<CGLVideoSink::IGLVideoSinkStrategy>& strategy);
			virtual ~CGLVideoSink(void);
	};

}

#endif // GLVIDEOSINK_H
