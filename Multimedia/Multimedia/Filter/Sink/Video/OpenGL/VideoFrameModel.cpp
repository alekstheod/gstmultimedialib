#include "VideoFrameModel.h"
#include <Utilities/AutoLock/AutoLock.h>
#include <algorithm>

namespace multimedia {

const unsigned int VideoFrameModel::CONST_FRAME_LOCK_TIMEOUT = 10000;

VideoFrameModel::VideoFrameModel(const gl::Vertex& lowLeft,
                                 const gl::Vertex& topLeft,
                                 const gl::Vertex& topRight,
                                 const gl::Vertex& lowRight): m_lowLeft(lowLeft),
    m_topLeft(topLeft),
    m_lowRight(lowRight),
    m_topRight(topRight),
    m_texture(0)
{
}

VideoFrameModel::~VideoFrameModel(void) {
    if( m_texture != 0 )
    {
        glDeleteTextures ( 1, &m_texture );
    }
}

void applyMaterial()
{
    float diffuseColor[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);

    float specColor[] = {1.0f, 0.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);

    float ambientColor[] = {1.2f, 1.2f, 1.2f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);

    float emmisionColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmisionColor);

    float shinines = 100.f;
    float strength = 100.f;
    unsigned int max = 1;

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
    float color[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
}

void VideoFrameModel::drawImpl(void) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if( !m_frameBuffer.empty() )
    {
        if( m_texture == 0 )
        {
            glGenTextures ( 1, &m_texture );
        }

        glEnable(GL_TEXTURE_2D);
        glBindTexture ( GL_TEXTURE_2D, m_texture );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexImage2D ( GL_TEXTURE_2D, 0, m_glColor, m_width, m_height, 0, m_glColor, m_pixelType, m_frameBuffer.data() );

        glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix

	glColor3f(1.f, 1.f, 1.f);
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
	glDisable(GL_TEXTURE_2D);
    }
}

bool VideoFrameModel::UpdateFrame(GLsizei width, GLsizei height, GLenum glColor,
                                  GLenum pixelType, GstBuffer* gstBuffer) {
    if( gstBuffer != NULL ) {
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

