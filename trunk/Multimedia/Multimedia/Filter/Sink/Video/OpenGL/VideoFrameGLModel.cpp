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
		_texture = 0;
		_gstBuffer=NULL;
		glGenTextures(1, &_texture);
	}

	VideoFrameGLModel::~VideoFrameGLModel(void) {
		glDeleteTextures(1, &_texture);
		if(_gstBuffer!=NULL){
			gst_buffer_unref(_gstBuffer);
		}
	}

	bool VideoFrameGLModel::drawModel(void) {
		try {
			AutoLock lock(_lockObject);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			if(_gstBuffer!=NULL){
				//glTexImage2D(GL_TEXTURE_2D, 0, 3, _width, _height, 0, _format, _type, GST_BUFFER_DATA(_gstBuffer) );
				gluBuild2DMipmaps( GL_TEXTURE_2D, 3, _width, _height,
				                   GL_RGB, GL_UNSIGNED_BYTE, GST_BUFFER_DATA(_gstBuffer)  );
			}

			glBegin(GL_QUADS);
			glBindTexture(GL_TEXTURE_2D, _texture);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(_lowLeft.getPosX(), _lowLeft.getPosY(), _lowLeft.getPosZ());

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(_lowRight.getPosX(), _lowRight.getPosY(), _lowRight.getPosZ());

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(_topRight.getPosX(), _topRight.getPosY(), _topRight.getPosZ());

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(_topLeft.getPosX(), _topLeft.getPosY(), _topLeft.getPosZ());

			glEnd();
		} catch (const LockException&) {
			return false;
		}

		return true;
	}

	bool VideoFrameGLModel::UpdateFrame(GLsizei width, GLsizei height, GLenum format, GLenum type, GstBuffer* gstBuffer) {
		try {
			AutoLock lock(_lockObject);
			if(_gstBuffer!=NULL){
				gst_buffer_unref(_gstBuffer);
				_gstBuffer=NULL;
			}

			if(gstBuffer!=NULL){
				_gstBuffer=gst_buffer_ref(gstBuffer);
			}

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

	bool VideoFrameGLModel::addRotationX(unsigned int rotationId, float angle){
		return true;
	}

	bool VideoFrameGLModel::addRotationY(unsigned int rotationId, float angle){
		return true;
	};

	bool VideoFrameGLModel::addRotationZ(unsigned int rotationId, float angle){
		return true;
	}

	bool VideoFrameGLModel::removeAllRotations(){
		return true;
	}

	bool VideoFrameGLModel::addRotationX(const std::string& objectName, unsigned int rotationId, float angle){
		return false;
	}

	bool VideoFrameGLModel::addRotationY(const std::string& objectName, unsigned int rotationId, float angle){
		return false;
	}

	bool VideoFrameGLModel::addRotationZ(const std::string& objectName, unsigned int rotationId, float angle){
		return false;
	}

	bool VideoFrameGLModel::removeAllRotations(const std::string& objectName){
		return false;
	}

}

