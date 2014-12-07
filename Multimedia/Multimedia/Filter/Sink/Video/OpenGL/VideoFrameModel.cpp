#include "VideoFrameModel.h"
#include <Utilities/AutoLock/AutoLock.h>
#include <GLEngine/Model/ImageTexture.h>
#include <algorithm>

namespace multimedia {

const unsigned int VideoFrameModel::CONST_FRAME_LOCK_TIMEOUT = 10000;

VideoFrameModel::VideoFrameModel(const gl::Vertex& lowLeft,
                                 const gl::Vertex& topLeft, 
				 const gl::Vertex& topRight,
                                 const gl::Vertex& lowRight): m_lowLeft(lowLeft),
							      m_topLeft(topLeft),
							      m_lowRight(lowRight),
							      m_topRight(topRight)
{
}

VideoFrameModel::~VideoFrameModel(void) {
}

void VideoFrameModel::drawImpl(void) {
    std::lock_guard<std::mutex> lock(m_mutex);
    gl::ImageTexture texture(m_width, m_height, m_glColor, m_pixelType, m_frameBuffer);
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
}

bool VideoFrameModel::UpdateFrame(GLsizei width, GLsizei height, GLenum glColor,
                                  GLenum pixelType, GstBuffer* gstBuffer) {
    if( gstBuffer != NULL ){
        if (m_backBuffer.size() != gstBuffer->size) {
            m_backBuffer.resize(gstBuffer->size);
        }

        std::copy(gstBuffer->data, gstBuffer->data + gstBuffer->size, m_backBuffer.begin());
    }
    
    std::lock_guard<std::mutex> lock(m_mutex);
    m_width = width;
    m_height = height;
    m_glColor = glColor;
    m_pixelType = pixelType;
    m_frameBuffer.swap(m_backBuffer);
    return true;
}

bool VideoFrameModel::UpdateFramePosition(const gl::Vertex& lowLeft,
        const gl::Vertex& topLeft, const gl::Vertex& topRight,
        const gl::Vertex& lowRight) {

    std::lock_guard<std::mutex> lock(m_mutex);
    m_lowLeft = lowLeft;
    m_lowRight = lowRight;
    m_topLeft = topLeft;
    m_topRight = topRight;
    return true;
}

}

