#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <string.h>
#include "VideoFrameGLModel.h"

namespace multimedia{

	const float CGLVideoSinkFilter::CONST_GL_FRAME_HEIGHT = 1.16;
	const float CGLVideoSinkFilter::CONST_GL_FRAME_WIDTH = 2;

	CGLVideoSinkFilter::CGLVideoSinkFilter(const utils::SmartPtr<gl::GLDevice>& glDevice)throw (GstException) : ABaseCallbackSinkFilter("GL Video sink") {
	    if (glDevice == NULL) {
	        throw GstException("GLVideoSink::GLVideoSink");
	    }

	    try {
	        _glDevice = glDevice;
	    } catch (const utils::LockException&) {
	        throw GstException("GLVideoSink::GLVideoSink");
	    }

	    float right = CONST_GL_FRAME_WIDTH / 2.0f;
	    float left = -right;
	    float high = CONST_GL_FRAME_HEIGHT / 2.0f;
	    float low = -high;
	    _lowLeft = gl::GLVertex(left, low, 0.0f);
	    _topRight = gl::GLVertex(right, high, 0.0f);
	    _lowRight = gl::GLVertex(right, low, 0.0f);
	    _topLeft = gl::GLVertex(left, high, 0.0f);

	    _videoFrameGLModel = new VideoFrameGLModel(_lowLeft, _topLeft, _topRight, _lowRight);
	    if (_videoFrameGLModel == NULL) {
	        throw GstException("GLVideoSink::GLVideoSink");
	    }

	    _glDevice->addGLModel(1, _videoFrameGLModel);
	}


	CGLVideoSinkFilter::~CGLVideoSinkFilter(void) {

	}


	bool CGLVideoSinkFilter::onSetCaps(GstPad * pad, GstCaps * caps) {
	    try {
	        utils::AutoLock lock(_lockObject);
	        if (_strategy != NULL) {
	            _strategy->OnSetCaps(caps);
	        }

	        GstStructure* gstStructure = gst_caps_get_structure(caps, 0);
	        if (gstStructure == NULL) {
	            return false;
	        }

	        if (!gst_structure_get_int(gstStructure, "width", &_frameWidth)) {
	            return false;
	        }

	        if (!gst_structure_get_int(gstStructure, "height", &_frameHeight)) {
	            return false;
	        }

	        const GValue* pixelFormat = gst_structure_get_value(gstStructure, "pixel-aspect-ratio");
	        if (pixelFormat == NULL) {
	            return false;
	        }

	        if (strcmp(gst_structure_get_name(gstStructure), "video/x-raw-rgb") == 0) {
	            gint red_color = 0;
	            gst_structure_get_int(gstStructure, "red_mask", &red_color);
	            if (red_color == gint(0xff000000)) {
	                _glColor = GL_RGBA;
	                _pixelType = GL_UNSIGNED_BYTE;
	            } else {
	                _glColor = GL_BGRA;
	                _pixelType = GL_UNSIGNED_BYTE;
	            }

	        } else {
	            _glColor = GL_YCBCR_MESA;
	            unsigned int fourcc;
	            gst_structure_get_fourcc(gstStructure, "format", &fourcc);
	            if (fourcc == GST_MAKE_FOURCC('Y', 'U', 'Y', '2')) {
	                _pixelType = GL_UNSIGNED_SHORT_8_8_REV_MESA;
	            } else {
	                _pixelType = GL_UNSIGNED_SHORT_8_8_MESA;
	            }
	        }

	    } catch (const utils::LockException&) {
	        return false;
	    }

	    return true;
	}


	bool CGLVideoSinkFilter::onRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer) {
	    try {
	        utils::AutoLock lock(_lockObject);
	        if (_strategy != NULL) {
	            _strategy->OnReceiveBuffer(gstBuffer);
	        }

	        VideoFrameGLModel* videoFrameGLModel = static_cast<VideoFrameGLModel*> (_videoFrameGLModel.getPtr());
	        if (videoFrameGLModel != NULL) {
	            videoFrameGLModel->UpdateFrame(_frameWidth, _frameHeight, _glColor, _pixelType, gstBuffer->data);
	        }

	    } catch (const utils::LockException&) {
	        return false;
	    }

	    return true;
	}


	bool CGLVideoSinkFilter::registerGLVideoSinkStrategy(const utils::SmartPtr<CGLVideoSinkFilter::IGLVideoSinkStrategy>& strategy) {
	    try {
	        utils::AutoLock lock(_lockObject);
	        _strategy.RegisterEventStrategy(strategy);

	    } catch (const utils::LockException&) {
	        return false;
	    }

	    return true;
	}

}


