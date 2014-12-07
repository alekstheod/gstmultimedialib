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
