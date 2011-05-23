#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLEngine/Model/IGLModel.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/GLVertex.h>
#include <Utilities/AutoLock/LLockObject.h>
#include <vector>

namespace multimedia {

	class VideoFrameGLModel: public gl::IGLModel {
		private:
			GLuint _texture;
			gl::GLVertex _lowLeft;
			gl::GLVertex _topLeft;
			gl::GLVertex _topRight;
			gl::GLVertex _lowRight;
			utils::LLockObject _lockObject;

			GLsizei _width;
			GLsizei _height;
			GLenum _format;
			GLenum _type;
			std::vector<unsigned char> _frameBuffer;

		public:
			VideoFrameGLModel(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
							const gl::GLVertex& lowRight) throw (gl::GLException);
			bool drawModel(void);
			bool UpdateFrame(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
			bool UpdateFramePosition(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
					const gl::GLVertex& lowRight);
			virtual bool addRotationX(unsigned int rotationId, float angle);
			virtual bool addRotationY(unsigned int rotationId, float angle);
			virtual bool addRotationZ(unsigned int rotationId, float angle);
			virtual bool removeAllRotations();
			virtual ~VideoFrameGLModel(void);
	};

}

