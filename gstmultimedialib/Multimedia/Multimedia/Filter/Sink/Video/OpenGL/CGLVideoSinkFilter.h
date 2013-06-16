#ifndef GLVIDEOSINK_H
#define GLVIDEOSINK_H
#include <GLEngine/Device.h>
#include <GLEngine/Model/Vertex.h>
#include <Multimedia/Filter/Sink/Video/ABaseVideoCallbackSinkFilter.h>
#include <Utilities/AutoLock/Mutex.h>

namespace multimedia
{

namespace Private
{
class CGLVideoSinkCallbackFilter : public ABaseVideoCallbackSinkFilter
{
private:
  gint _frameRate;
  gint _frameWidth;
  gint _frameHeight;
  GLenum _glColor;
  GLenum _pixelType;

  gl::Vertex _lowLeft;
  gl::Vertex _lowRight;
  gl::Vertex _topRight;
  gl::Vertex _topLeft;

  utils::Mutex _lockObject;

  utils::SharedPtr<gl::Device> _glDevice;
  utils::SharedPtr<gl::IModel> _videoFrameGLModel;

public:
  static const float CONST_GL_FRAME_HEIGHT;
  static const float CONST_GL_FRAME_WIDTH;
  static const GLuint CONST_INVALID_TEXTURE_ID;
  static const GLuint CONST_VALID_TEXTURE_ID;
  static const unsigned int CONST_VIDEOFRAME_GLMODEL_ID;

protected:
  bool onRecieveBuffer ( GstBaseSink* sink, GstBuffer* gstBuffer );
  bool onSetCaps ( GstPad * pad, GstCaps * caps );

private:
  CGLVideoSinkCallbackFilter ( const CGLVideoSinkCallbackFilter& other );
  const CGLVideoSinkCallbackFilter& operator = ( const CGLVideoSinkCallbackFilter& other );

public:
  CGLVideoSinkCallbackFilter ( const utils::SharedPtr<gl::Device>& glDevice ) throw ( GstException );
  virtual ~CGLVideoSinkCallbackFilter ( void );
};
}


class CGLVideoSinkFilter : public AFilter
{
private:
  utils::SharedPtr< Private::CGLVideoSinkCallbackFilter > _filter;

public:
  CGLVideoSinkFilter ( const utils::SharedPtr<gl::Device>& glDevice ) throw ( GstException );
  bool addToPipeline ( GstElement* pipeline ) ;
  ~CGLVideoSinkFilter();
};

}

#endif // GLVIDEOSINK_H
