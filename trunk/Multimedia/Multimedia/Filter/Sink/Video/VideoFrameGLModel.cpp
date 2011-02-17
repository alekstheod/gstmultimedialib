#include "VideoFrameGLModel.h"
#include <Utilities/AutoLock/AutoLock.h>
#include <string.h>

using namespace utils;

namespace multimedia {

	VideoFrameGLModel::VideoFrameGLModel(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
			const gl::GLVertex& lowRight) throw (gl::GLException) {
		_lowLeft = lowLeft;
		_topLeft = topLeft;
		_lowRight = lowRight;
		_topRight = topRight;
		glGenTextures(1, &_texture);
	}

	VideoFrameGLModel::~VideoFrameGLModel(void) {
		glDeleteTextures(1, &_texture);
	}

	bool VideoFrameGLModel::DrawModel(void) {
		try {
			AutoLock lock(_lockObject);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(_lowLeft.GetPosX(), _lowLeft.GetPosY(), _lowLeft.GetPosZ());
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(_lowRight.GetPosX(), _lowRight.GetPosY(), _lowRight.GetPosZ());
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(_topRight.GetPosX(), _topRight.GetPosY(), _topRight.GetPosZ());
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(_topLeft.GetPosX(), _topLeft.GetPosY(), _topLeft.GetPosZ());
			glEnd();
		} catch (const LockException&) {
			return false;
		}

		return true;
	}

	bool VideoFrameGLModel::UpdateFrame(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) {
		try {
			AutoLock lock(_lockObject);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, _width, _height, 0, _format, _type, pixels);
		} catch (const LockException&) {
			return false;
		}

		return true;
	}

	bool VideoFrameGLModel::UpdateFramePosition(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
			const gl::GLVertex& lowRight) {
		try {
			AutoLock lock(_lockObject);
			_lowLeft = lowLeft;
			_lowRight = lowRight;
			_topLeft = topLeft;
			_topRight = topRight;
		} catch (const LockException&) {
			return false;
		}

		return true;
	}

}

