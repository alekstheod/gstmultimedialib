#ifndef GLVIDEOSINK_H
#define GLVIDEOSINK_H
#include <GLEngine/Scene.h>
#include <GLEngine/Model/Vertex.h>
#include <Multimedia/Filter/Sink/Video/ABaseVideoCallbackSinkFilter.h>
#include <Multimedia/Filter/Sink/Video/OpenGL/VideoFrameModel.h>
#include <memory>

namespace multimedia
{

namespace detail
{
class CGLVideoSinkCallbackFilter : public ABaseVideoCallbackSinkFilter
{
private:
  gint _frameRate;
  gint _frameWidth;
  gint _frameHeight;
  GLenum _glColor;
  GLenum _pixelType;

  utils::Mutex _lockObject;

  gl::Scene& m_glDevice;
  multimedia::VideoFrameModel m_videoFrameGLModel;

public:
  static const float CONST_GL_FRAME_HEIGHT;
  static const float CONST_GL_FRAME_WIDTH;
  static const GLuint CONST_INVALID_TEXTURE_ID;
  static const GLuint CONST_VALID_TEXTURE_ID;
  static const unsigned int CONST_VIDEOFRAME_GLMODEL_ID;

private:
  bool onRecieveBuffer ( GstBaseSink* sink, GstBuffer* gstBuffer );
  bool onSetCaps ( GstPad * pad, GstCaps * caps );

public:
  CGLVideoSinkCallbackFilter ( gl::Scene& glDevice );
  virtual ~CGLVideoSinkCallbackFilter ( void );
};
}


class CGLVideoSinkFilter : public AFilter
{
private:
  std::shared_ptr<detail::CGLVideoSinkCallbackFilter> m_filter;

private:
    bool addToPipelineImpl ( GstElement* pipeline ) ;
    
public:
  CGLVideoSinkFilter ( gl::Scene& glDevice );
  ~CGLVideoSinkFilter();
};

}

#endif // GLVIDEOSINK_H
