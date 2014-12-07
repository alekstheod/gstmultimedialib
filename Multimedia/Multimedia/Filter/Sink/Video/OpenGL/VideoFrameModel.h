#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLEngine/Model/IModel.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/Vertex.h>
#include <mutex>
#include <vector>
#include <gst/gst.h>
#include <Utilities/Memory/SmartPtr/SharedPtr.h>

namespace multimedia {

class VideoFrameModel: public gl::IModel {
public:
    static const unsigned int CONST_FRAME_LOCK_TIMEOUT;

private:
    gl::Vertex m_lowLeft;
    gl::Vertex m_topLeft;
    gl::Vertex m_topRight;
    gl::Vertex m_lowRight;
    std::mutex m_mutex;

    GLsizei m_width;
    GLsizei m_height;
    GLenum m_glColor;
    GLenum m_pixelType;
    std::vector<unsigned char> m_backBuffer;
    std::vector<unsigned char> m_frameBuffer;

private:
    void drawImpl();
    bool UpdateFramePosition(const gl::Vertex& lowLeft,const gl::Vertex& topLeft, const gl::Vertex& topRight,const gl::Vertex& lowRight);
    
public:
    VideoFrameModel(const gl::Vertex& lowLeft, const gl::Vertex& topLeft,
                    const gl::Vertex& topRight, const gl::Vertex& lowRight);
    bool UpdateFrame(GLsizei width, GLsizei height, GLenum glColor, GLenum pixelType, GstBuffer* gstBuffer);
    virtual ~VideoFrameModel(void);
};

}

