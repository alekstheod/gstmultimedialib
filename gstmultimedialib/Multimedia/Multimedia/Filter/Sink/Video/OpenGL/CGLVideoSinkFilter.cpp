#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <string.h>
#include "VideoFrameModel.h"

namespace multimedia {

const float CGLVideoSinkFilter::CONST_GL_FRAME_HEIGHT = 1.16;
const float CGLVideoSinkFilter::CONST_GL_FRAME_WIDTH = 2;
const GLuint CGLVideoSinkFilter::CONST_INVALID_TEXTURE_ID = 0;
const unsigned int CGLVideoSinkFilter::CONST_VIDEOFRAME_GLMODEL_ID = 1;

CGLVideoSinkFilter::CGLVideoSinkFilter(
		const utils::SmartPtr<gl::Device>& glDevice) throw (GstException) :
		ABaseVideoCallbackSinkFilter("GL Video sink") {
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
	_lowLeft = gl::Vertex(left, low, 0.0f);
	_topRight = gl::Vertex(right, high, 0.0f);
	_lowRight = gl::Vertex(right, low, 0.0f);
	_topLeft = gl::Vertex(left, high, 0.0f);

	_videoFrameGLModel = new VideoFrameModel(_lowLeft, _topLeft, _topRight,
			_lowRight);
	if (_videoFrameGLModel == NULL) {
		throw GstException("GLVideoSink::GLVideoSink");
	}

	if (!_glDevice->addGLModel(_videoFrameGLModel)) {
		throw GstException("GLVideoSink::GLVideoSink");
	}
}

CGLVideoSinkFilter::~CGLVideoSinkFilter(void) {
}

bool CGLVideoSinkFilter::onSetCaps(GstPad * pad, GstCaps * caps) {
	try {
		utils::AutoLock lock(_lockObject);
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

		const GValue* pixelFormat = gst_structure_get_value(gstStructure,
				"pixel-aspect-ratio");
		if (pixelFormat == NULL) {
			return false;
		}

		if (strcmp(gst_structure_get_name(gstStructure), "video/x-raw-rgb")
				== 0) {
			gint red_color = 0;
			gst_structure_get_int(gstStructure, "red_mask", &red_color);
			if (red_color == gint(0xff000000)) {
				_glColor = GL_RGBA;
				_pixelType = GL_UNSIGNED_BYTE;
			} else {
				_glColor = GL_BGRA;
				_pixelType = GL_UNSIGNED_BYTE;
			}

		} else if (strcmp(gst_structure_get_name(gstStructure),
				"video/x-raw-yuv") == 0) {
			_glColor = GL_YCBCR_MESA;
			unsigned int fourcc;
			gst_structure_get_fourcc(gstStructure, "format", &fourcc);
			if (fourcc == GST_MAKE_FOURCC('Y', 'U', 'Y', '2')) {
				_pixelType = GL_UNSIGNED_SHORT_8_8_REV_MESA;
			} else {
				_pixelType = GL_UNSIGNED_SHORT_8_8_MESA;
			}
		} else {
			return false;
		}

	} catch (const utils::LockException&) {
		return false;
	}

	return true;
}

bool CGLVideoSinkFilter::onRecieveBuffer(GstBaseSink* sink,
		GstBuffer* gstBuffer) {
	try {
		utils::AutoLock lock(_lockObject);
		VideoFrameModel* videoFrameGLModel =
				static_cast<VideoFrameModel*>(_videoFrameGLModel.getPtr());
		if (videoFrameGLModel != NULL) {
			videoFrameGLModel->UpdateFrame(_frameWidth, _frameHeight, _glColor,
					_pixelType, gstBuffer);
		}

	} catch (const utils::LockException&) {
		return false;
	}

	return true;
}

}

