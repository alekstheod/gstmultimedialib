#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLEngine/Model/IModel.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/Vertex.h>
#include <Utilities/AutoLock/LLockObject.h>
#include <vector>
#include <gst/gst.h>
#include <Utilities/SmartPtr/SmartPtr.h>

namespace multimedia {

	class VideoFrameModel: public gl::IModel {
		public:
			static const unsigned int CONST_FRAME_LOCK_TIMEOUT;

		private:
			gl::Vertex _lowLeft;
			gl::Vertex _topLeft;
			gl::Vertex _topRight;
			gl::Vertex _lowRight;
			utils::LLockObject _lockObject;

			GLsizei _width;
			GLsizei _height;
			GLenum _glColor;
			GLenum _pixelType;
			std::vector<unsigned char> _frameBuffer;

		public:
			VideoFrameModel(const gl::Vertex& lowLeft,
							const gl::Vertex& topLeft,
							const gl::Vertex& topRight,
							const gl::Vertex& lowRight) throw (gl::GLException);

			bool drawModel(void);
			bool UpdateFrame( GLsizei width, GLsizei height, GLenum glColor, GLenum pixelType, GstBuffer* gstBuffer );
			bool UpdateFramePosition( const gl::Vertex& lowLeft, const gl::Vertex& topLeft, const gl::Vertex& topRight, const gl::Vertex& lowRight );
			bool addRotationX(unsigned int rotationId, float angle);
			bool addRotationY(unsigned int rotationId, float angle);
			bool addRotationZ(unsigned int rotationId, float angle);

			bool addRotationX(const std::string& objectName, unsigned int rotationId, float angle);
			bool addRotationY(const std::string& objectName, unsigned int rotationId, float angle);
			bool addRotationZ(const std::string& objectName, unsigned int rotationId, float angle);
			bool removeAllRotations(const std::string& objectName);

			bool removeAllRotations();
			virtual ~VideoFrameModel(void);
	};

}

