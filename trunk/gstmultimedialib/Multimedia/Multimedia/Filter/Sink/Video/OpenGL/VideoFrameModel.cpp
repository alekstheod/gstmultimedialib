#include "VideoFrameModel.h"
#include <Utilities/AutoLock/AutoLock.h>
#include <GLEngine/Model/ImageTexture.h>
#include <algorithm>

namespace multimedia {

const unsigned int VideoFrameModel::CONST_FRAME_LOCK_TIMEOUT = 10000;

VideoFrameModel::VideoFrameModel(const gl::Vertex& lowLeft,
                                 const gl::Vertex& topLeft, const gl::Vertex& topRight,
                                 const gl::Vertex& lowRight) {
    m_lowLeft = lowLeft;
    m_topLeft = topLeft;
    m_lowRight = lowRight;
    m_topRight = topRight;
}

VideoFrameModel::~VideoFrameModel(void) {
}

bool VideoFrameModel::drawImpl(void) {
    try {
        utils::AutoLock<utils::Mutex> lock(m_lockObject);
        gl::ImageTexture texture(1000, m_width, m_height, m_glColor, m_pixelType, m_frameBuffer);
        texture.apply(GL_TEXTURE_2D);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(m_lowLeft.x, m_lowLeft.y, m_lowLeft.z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(m_lowRight.x, m_lowRight.y,
                   m_lowRight.z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(m_topRight.x, m_topRight.y,
                   m_topRight.z);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(m_topLeft.x, m_topLeft.y, m_topLeft.z);
        glEnd();
    } catch (const utils::LockException&) {
        return false;
    }

    return true;
}

bool VideoFrameModel::UpdateFrame(GLsizei width, GLsizei height, GLenum glColor,
                                  GLenum pixelType, GstBuffer* gstBuffer) {
    try {
        utils::AutoLock<utils::Mutex> lock(m_lockObject);
        m_width = width;
        m_height = height;
        m_glColor = glColor;
        m_pixelType = pixelType;
        if (gstBuffer != NULL) {
            if (m_frameBuffer.size() != gstBuffer->size) {
                m_frameBuffer.resize(gstBuffer->size);
            }

            std::copy(gstBuffer->data, gstBuffer->data + gstBuffer->size,
                      m_frameBuffer.begin());
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
        utils::AutoLock<utils::Mutex> lock(m_lockObject);
        m_lowLeft = lowLeft;
        m_lowRight = lowRight;
        m_topLeft = topLeft;
        m_topRight = topRight;
    } catch (const utils::LockException&) {
        return false;
    }

    return true;
}

}

