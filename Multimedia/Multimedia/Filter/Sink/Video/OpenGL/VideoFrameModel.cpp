#include "VideoFrameModel.h"
#include <Utilities/AutoLock/AutoLock.h>

namespace multimedia {

	const unsigned int VideoFrameModel::CONST_FRAME_LOCK_TIMEOUT=1000;

	VideoFrameModel::VideoFrameModel(const gl::Vertex& lowLeft, const gl::Vertex& topLeft, const gl::Vertex& topRight,
			const gl::Vertex& lowRight) throw (gl::GLException) {
		_lowLeft = lowLeft;
		_topLeft = topLeft;
		_lowRight = lowRight;
		_topRight = topRight;
		_gstBuffer=NULL;
		_texture=0;
		_lockObject.lock();
	}

	VideoFrameModel::~VideoFrameModel(void) {
	}

	bool VideoFrameModel::drawModel(void) {
		try {
			utils::AutoLock lock(_lockObject, CONST_FRAME_LOCK_TIMEOUT);
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
			glTexCoord2f( 0.0f, 1.0f );
			glVertex3f(_lowLeft.getPosX(), _lowLeft.getPosY(), _lowLeft.getPosZ());

			glTexCoord2f( 1.0f, 1.0f );
			glVertex3f(_lowRight.getPosX(), _lowRight.getPosY(), _lowRight.getPosZ());

			glTexCoord2f( 1.0f, 0.0f );
			glVertex3f( _topRight.getPosX(), _topRight.getPosY(), _topRight.getPosZ() );

			glTexCoord2f( 0.0f, 0.0f );
			glVertex3f( _topLeft.getPosX(), _topLeft.getPosY(), _topLeft.getPosZ() );
			glEnd();
		} catch (const utils::LockException&) {
			return false;
		}

		return true;
	}

	bool VideoFrameModel::UpdateFrame(GLuint texture, GLsizei width, GLsizei height, GLenum glColor, GLenum pixelType, GstBuffer* gstBuffer) {
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

	bool VideoFrameModel::UpdateFramePosition(const gl::Vertex& lowLeft, const gl::Vertex& topLeft, const gl::Vertex& topRight,
		const gl::Vertex& lowRight) {
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

	bool VideoFrameModel::addRotationX(unsigned int rotationId, float angle){
		return true;
	}

	bool VideoFrameModel::addRotationY(unsigned int rotationId, float angle){
		return true;
	};

	bool VideoFrameModel::addRotationZ(unsigned int rotationId, float angle){
		return true;
	}

	bool VideoFrameModel::removeAllRotations(){
		return true;
	}

	bool VideoFrameModel::addRotationX(const std::string& objectName, unsigned int rotationId, float angle){
		return false;
	}

	bool VideoFrameModel::addRotationY(const std::string& objectName, unsigned int rotationId, float angle){
		return false;
	}

	bool VideoFrameModel::addRotationZ(const std::string& objectName, unsigned int rotationId, float angle){
		return false;
	}

	bool VideoFrameModel::removeAllRotations(const std::string& objectName){
		return false;
	}

}

