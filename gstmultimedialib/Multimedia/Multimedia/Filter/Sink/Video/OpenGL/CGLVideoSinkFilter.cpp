#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <string.h>
#include "VideoFrameModel.h"
#include <mutex>

namespace multimedia
{

namespace detail
{

float right = 1.f;
float left = -right;
float high = 1.16f / 2.0f;
float low = -high;

gl::Vertex lowLeft( left, low, 0.0f );
gl::Vertex lowRight( right, low, 0.0f );
gl::Vertex topRight( right, high, 0.0f );
gl::Vertex topLeft( left, high, 0.0f );

CGLVideoSinkCallbackFilter::CGLVideoSinkCallbackFilter (gl::Scene& glDevice ):ABaseVideoCallbackSinkFilter ( "GL Video sink" ),
    m_glDevice(glDevice),
    m_videoFrameGLModel(lowLeft, topLeft, topRight, lowRight)
{
    m_glDevice.add ( m_videoFrameGLModel );
}

CGLVideoSinkCallbackFilter::~CGLVideoSinkCallbackFilter ( void )
{
    m_glDevice.remove(m_videoFrameGLModel);
}

bool CGLVideoSinkCallbackFilter::onSetCaps ( GstPad * pad, GstCaps * caps )
{
    try
    {
        std::lock_guard<std::mutex> lock( m_lock );
        GstStructure* gstStructure = gst_caps_get_structure ( caps, 0 );
        if ( gstStructure == NULL ||
                !gst_structure_get_int ( gstStructure, "width", &m_width ) ||
                !gst_structure_get_int ( gstStructure, "height", &m_height )
           ){
            return false;
        }

        const GValue* pixelFormat = gst_structure_get_value ( gstStructure,
                                    "pixel-aspect-ratio" );
        if ( pixelFormat == NULL ){
            return false;
        }

        if ( strcmp ( gst_structure_get_name ( gstStructure ), "video/x-raw-rgb" ) == 0 ){
            gint red_color = 0;
            gst_structure_get_int ( gstStructure, "red_mask", &red_color );
            if ( red_color == gint ( 0xff000000 ) )
            {
                m_glColor = GL_RGBA;
                m_pixelType = GL_UNSIGNED_BYTE;
            }
            else
            {
                m_glColor = GL_BGRA;
                m_pixelType = GL_UNSIGNED_BYTE;
            }

        }else if ( strcmp ( gst_structure_get_name ( gstStructure ), "video/x-raw-yuv" ) == 0 ){
            m_glColor = GL_YCBCR_MESA;
            unsigned int fourcc;
            gst_structure_get_fourcc ( gstStructure, "format", &fourcc );
            if ( fourcc == GST_MAKE_FOURCC ( 'Y', 'U', 'Y', '2' ) )
            {
                m_pixelType = GL_UNSIGNED_SHORT_8_8_REV_MESA;
            }
            else
            {
                m_pixelType = GL_UNSIGNED_SHORT_8_8_MESA;
            }
        }else{
            return false;
        }

    }catch ( const std::exception& ){
        return false;
    }

    return true;
}

bool CGLVideoSinkCallbackFilter::onRecieveBuffer ( GstBaseSink* sink,
        GstBuffer* gstBuffer )
{
    try{
        std::lock_guard<std::mutex> lock( m_lock );
        m_videoFrameGLModel.UpdateFrame ( m_width, m_height, m_glColor,
                                          m_pixelType, gstBuffer );

    }catch ( const std::exception& ){
        return false;
    }

    return true;
}

}

CGLVideoSinkFilter::CGLVideoSinkFilter ( gl::Scene& glDevice ): m_filter ( new detail::CGLVideoSinkCallbackFilter(glDevice) )
{
}

bool CGLVideoSinkFilter::addToPipelineImpl ( GstElement* pipeline )
{
    return m_filter->addToPipeline ( pipeline );
}

CGLVideoSinkFilter::~CGLVideoSinkFilter()
{
}

}

