#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <string.h>
#include "VideoFrameModel.h"

namespace multimedia
{

namespace Private
{
const float CGLVideoSinkCallbackFilter::CONST_GL_FRAME_HEIGHT = 1.16;
const float CGLVideoSinkCallbackFilter::CONST_GL_FRAME_WIDTH = 2;
const GLuint CGLVideoSinkCallbackFilter::CONST_INVALID_TEXTURE_ID = 0;
const unsigned int CGLVideoSinkCallbackFilter::CONST_VIDEOFRAME_GLMODEL_ID = 1;

CGLVideoSinkCallbackFilter::CGLVideoSinkCallbackFilter (
  const utils::SharedPtr<gl::Device>& glDevice ) throw ( GstException ) :  ABaseVideoCallbackSinkFilter ( "GL Video sink" )
{
  if ( glDevice == NULL )
    {
      throw GstException ( "CGLVideoSinkFilter::CGLVideoSinkFilter glDevice == NULL" );
    }

  _glDevice = glDevice;
  float right = CONST_GL_FRAME_WIDTH / 2.0f;
  float left = -right;
  float high = CONST_GL_FRAME_HEIGHT / 2.0f;
  float low = -high;
  _lowLeft = gl::Vertex ( left, low, 0.0f );
  _topRight = gl::Vertex ( right, high, 0.0f );
  _lowRight = gl::Vertex ( right, low, 0.0f );
  _topLeft = gl::Vertex ( left, high, 0.0f );

  _videoFrameGLModel = new VideoFrameModel ( _lowLeft, _topLeft, _topRight,_lowRight );
  utils::SharedPtr< gl::IModel > glModel = _videoFrameGLModel;
  if ( !_glDevice->addGLModel ( glModel ) )
    {
      throw GstException ( "GLVideoSink::GLVideoSink" );
    }
}

CGLVideoSinkCallbackFilter::~CGLVideoSinkCallbackFilter ( void )
{
  _glDevice->removeGLModel(_videoFrameGLModel);
}

bool CGLVideoSinkCallbackFilter::onSetCaps ( GstPad * pad, GstCaps * caps )
{
  try
    {
      utils::AutoLock<utils::Mutex> lock ( _lockObject );
      GstStructure* gstStructure = gst_caps_get_structure ( caps, 0 );
      if ( gstStructure == NULL )
        {
          return false;
        }

      if ( !gst_structure_get_int ( gstStructure, "width", &_frameWidth ) )
        {
          return false;
        }

      if ( !gst_structure_get_int ( gstStructure, "height", &_frameHeight ) )
        {
          return false;
        }

      const GValue* pixelFormat = gst_structure_get_value ( gstStructure,
                                  "pixel-aspect-ratio" );
      if ( pixelFormat == NULL )
        {
          return false;
        }

      if ( strcmp ( gst_structure_get_name ( gstStructure ), "video/x-raw-rgb" )
           == 0 )
        {
          gint red_color = 0;
          gst_structure_get_int ( gstStructure, "red_mask", &red_color );
          if ( red_color == gint ( 0xff000000 ) )
            {
              _glColor = GL_RGBA;
              _pixelType = GL_UNSIGNED_BYTE;
            }
          else
            {
              _glColor = GL_BGRA;
              _pixelType = GL_UNSIGNED_BYTE;
            }

        }
      else if ( strcmp ( gst_structure_get_name ( gstStructure ),
                         "video/x-raw-yuv" ) == 0 )
        {
          _glColor = GL_YCBCR_MESA;
          unsigned int fourcc;
          gst_structure_get_fourcc ( gstStructure, "format", &fourcc );
          if ( fourcc == GST_MAKE_FOURCC ( 'Y', 'U', 'Y', '2' ) )
            {
              _pixelType = GL_UNSIGNED_SHORT_8_8_REV_MESA;
            }
          else
            {
              _pixelType = GL_UNSIGNED_SHORT_8_8_MESA;
            }
        }
      else
        {
          return false;
        }

    }
  catch ( const utils::LockException& )
    {
      return false;
    }

  return true;
}

bool CGLVideoSinkCallbackFilter::onRecieveBuffer ( GstBaseSink* sink,
    GstBuffer* gstBuffer )
{
  try
    {
      utils::AutoLock<utils::Mutex> lock ( _lockObject );
      if ( _videoFrameGLModel != NULL )
        {
          _videoFrameGLModel->UpdateFrame ( _frameWidth, _frameHeight, _glColor,
                                           _pixelType, gstBuffer );
        }

    }
  catch ( const utils::LockException& )
    {
      return false;
    }

  return true;
}

}

CGLVideoSinkFilter::CGLVideoSinkFilter ( const utils::SharedPtr<gl::Device>& glDevice ) throw ( GstException ) : _filter ( new Private::CGLVideoSinkCallbackFilter ( glDevice ) )
{
}

bool CGLVideoSinkFilter::addToPipeline ( GstElement* pipeline )
{
  return _filter->addToPipeline ( pipeline );
}

CGLVideoSinkFilter::~CGLVideoSinkFilter()
{
}

}

