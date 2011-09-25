#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLEngine/Model/IGLModel.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/GLVertex.h>
#include <Utilities/AutoLock/LLockObject.h>
#include <vector>
#include <gst/gst.h>

namespace multimedia {

	class VideoFrameGLModel: public gl::IGLModel {
		public:
			static const unsigned int CONST_FRAME_LOCK_TIMEOUT;

		private:
			gl::GLVertex _lowLeft;
			gl::GLVertex _topLeft;
			gl::GLVertex _topRight;
			gl::GLVertex _lowRight;
			utils::LLockObject _lockObject;

			GLsizei _width;
			GLsizei _height;
			GLenum _glColor;
			GLenum _pixelType;
			//std::vector<unsigned char> _frameBuffer;
			GstBuffer* _gstBuffer;
			GLuint _texture;

		public:
			VideoFrameGLModel(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
							const gl::GLVertex& lowRight) throw (gl::GLException);
			bool drawModel(void);
			bool UpdateFrame(GLuint texture, GLsizei width, GLsizei height, GLenum glColor, GLenum pixelType, GstBuffer* gstBuffer);
			bool UpdateFramePosition(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
					const gl::GLVertex& lowRight);
			bool addRotationX(unsigned int rotationId, float angle);
			bool addRotationY(unsigned int rotationId, float angle);
			bool addRotationZ(unsigned int rotationId, float angle);

			bool addRotationX(const std::string& objectName, unsigned int rotationId, float angle);
			bool addRotationY(const std::string& objectName, unsigned int rotationId, float angle);
			bool addRotationZ(const std::string& objectName, unsigned int rotationId, float angle);
			bool removeAllRotations(const std::string& objectName);

			bool removeAllRotations();
			virtual ~VideoFrameGLModel(void);
	};

}

