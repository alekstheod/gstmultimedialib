#include "VideoFrameModel.h"
#include <Utilities/AutoLock/AutoLock.h>
#include <GLEngine/Model/ImageTexture.h>
#include <algorithm>

namespace multimedia {

const unsigned int VideoFrameModel::CONST_FRAME_LOCK_TIMEOUT = 10000;

VideoFrameModel::VideoFrameModel(const gl::Vertex& lowLeft,
                                 const gl::Vertex& topLeft, const gl::Vertex& topRight,
                                 const gl::Vertex& lowRight) throw (gl::GLException) {
    _lowLeft = lowLeft;
    _topLeft = topLeft;
    _lowRight = lowRight;
    _topRight = topRight;
}

VideoFrameModel::~VideoFrameModel(void) {
}

bool VideoFrameModel::drawModel(void) {
    try {
        utils::AutoLock<utils::Mutex> lock(_lockObject);
        gl::ImageTexture texture(1000, _width, _height, _glColor, _pixelType);
        if (!_frameBuffer.empty()) {
            texture.applyTexture(GL_TEXTURE_2D, _frameBuffer);
        }

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(_lowLeft.x, _lowLeft.y, _lowLeft.z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(_lowRight.x, _lowRight.y,
                   _lowRight.z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(_topRight.x, _topRight.y,
                   _topRight.z);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(_topLeft.x, _topLeft.y, _topLeft.z);
        glEnd();
    } catch (const utils::LockException&) {
        return false;
    }

    return true;
}

bool VideoFrameModel::UpdateFrame(GLsizei width, GLsizei height, GLenum glColor,
                                  GLenum pixelType, GstBuffer* gstBuffer) {
    try {
        utils::AutoLock<utils::Mutex> lock(_lockObject);
        _width = width;
        _height = height;
        _glColor = glColor;
        _pixelType = pixelType;
        if (gstBuffer != NULL) {
            if (_frameBuffer.size() != gstBuffer->size) {
                _frameBuffer.resize(gstBuffer->size);
            }

            std::copy(gstBuffer->data, gstBuffer->data + gstBuffer->size,
                      _frameBuffer.begin());
        }
    } catch (const utils::LockException&) {
        return false;
    }

    return true;
}

bool VideoFrameModel::UpdateFramePosition(const gl::Vertex& lowLeft,
        const gl::Vertex& topLeft, const gl::Vertex& topRight,
        const gl::Vertex& lowRight) {
    try {
        utils::AutoLock<utils::Mutex> lock(_lockObject);
        _lowLeft = lowLeft;
        _lowRight = lowRight;
        _topLeft = topLeft;
        _topRight = topRight;
    } catch (const utils::LockException&) {
        return false;
    }

    return true;
}

bool VideoFrameModel::addRotationX(unsigned int rotationId, float angle) {
    return true;
}

bool VideoFrameModel::addRotationY(unsigned int rotationId, float angle) {
    return true;
}
;

bool VideoFrameModel::addRotationZ(unsigned int rotationId, float angle) {
    return true;
}

bool VideoFrameModel::removeAllRotations() {
    return true;
}

bool VideoFrameModel::addRotationX(const std::string& objectName,
                                   unsigned int rotationId, float angle) {
    return false;
}

bool VideoFrameModel::addRotationY(const std::string& objectName,
                                   unsigned int rotationId, float angle) {
    return false;
}

bool VideoFrameModel::addRotationZ(const std::string& objectName,
                                   unsigned int rotationId, float angle) {
    return false;
}

bool VideoFrameModel::removeAllRotations(const std::string& objectName) {
    return false;
}

}

