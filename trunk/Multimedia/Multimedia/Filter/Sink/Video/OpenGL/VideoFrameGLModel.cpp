#include "VideoFrameGLModel.h"
#include <Utilities/AutoLock/AutoLock.h>

namespace multimedia {

	const unsigned int VideoFrameGLModel::CONST_FRAME_LOCK_TIMEOUT=10000;

	VideoFrameGLModel::VideoFrameGLModel(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
			const gl::GLVertex& lowRight) throw (gl::GLException) {
		_lowLeft = lowLeft;
		_topLeft = topLeft;
		_lowRight = lowRight;
		_topRight = topRight;
		_gstBuffer=NULL;
		_texture=0;
		_lockObject.lock();
	}

	VideoFrameGLModel::~VideoFrameGLModel(void) {
	}

	bool VideoFrameGLModel::drawModel(void) {
		try {
			utils::AutoLock lock(_lockObject);
			if(_texture==0 || _gstBuffer==NULL){
				return false;
			}

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			if(_gstBuffer!=NULL){
				glTexImage2D (GL_TEXTURE_2D, 0, _glColor, _width, _height, 0, _glColor, _pixelType, NULL);
				glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, _width, _height,_glColor, _pixelType, GST_BUFFER_DATA (_gstBuffer));
			}

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(_lowLeft.getPosX(), _lowLeft.getPosY(), _lowLeft.getPosZ());

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(_lowRight.getPosX(), _lowRight.getPosY(), _lowRight.getPosZ());

			glTexCoord2f( 1.0f, 0.0f );
			glVertex3f( _topRight.getPosX(), _topRight.getPosY(), _topRight.getPosZ() );

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(_topLeft.getPosX(), _topLeft.getPosY(), _topLeft.getPosZ());
			glEnd();
		} catch (const utils::LockException&) {
			return false;
		}

		return true;
	}

	bool VideoFrameGLModel::UpdateFrame(GLuint texture, GLsizei width, GLsizei height, GLenum glColor, GLenum pixelType, GstBuffer* gstBuffer) {
		_width=width;
		_height=height;
		_glColor=glColor;
		_pixelType=pixelType;
		_texture=texture;
		_gstBuffer=gstBuffer;
		_lockObject.unlock();

		usleep(CONST_FRAME_LOCK_TIMEOUT);

		_lockObject.lock();
		_gstBuffer=NULL;
		return true;
	}

	bool VideoFrameGLModel::UpdateFramePosition(const gl::GLVertex& lowLeft, const gl::GLVertex& topLeft, const gl::GLVertex& topRight,
			const gl::GLVertex& lowRight) {
		try {
			utils::AutoLock lock(_lockObject);
			_lowLeft = lowLeft;
			_lowRight = lowRight;
			_topLeft = topLeft;
			_topRight = topRight;
		} catch (const utils::LockException&) {
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

