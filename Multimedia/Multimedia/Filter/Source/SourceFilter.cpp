/*
 * SourceFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Source/SourceFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseOutputFilter.h>

namespace multimedia {

	const std::string SourceFilter::CONST_PLUGIN_NAME = "filesrc";

	SourceFilter::SourceFilter(const std::string& fileName) throw (GstException) {
		if (fileName.empty()) {
			throw GstException("SourceFilter::SourceFilter - Empty fileName");
		}
		_source = gst_element_factory_make(CONST_PLUGIN_NAME.c_str(), fileName.c_str());
		if (_source == NULL) {
			throw GstException("SourceFilter::SourceFilter - File source create failed");
		}

		g_object_set(G_OBJECT(_source.GetPtr()), "location", fileName.c_str(), NULL);
	}

	bool SourceFilter::AddToPipeline(GstElement* pipeline) {
		if (pipeline == NULL) {
			return false;
		}

		return gst_bin_add(GST_BIN(pipeline), _source.GetPtr());
	}

	bool SourceFilter::Connect(BaseDemuxerFilter* demuxer) {
		if (demuxer == NULL) {
			return false;
		}

		gst_object_ref(static_cast<GstElement*> (_source.GetPtr()));
		return gst_element_link(_source.GetPtr(), demuxer->_demuxer.GetPtr());
	}

	bool SourceFilter::Connect(BaseOutputFilter* output) {
		if (output == NULL) {
			return false;
		}

		gst_object_ref(static_cast<GstElement*> (_source.GetPtr()));
		return gst_element_link(_source.GetPtr(), output->_output.GetPtr());
	}

	SourceFilter::~SourceFilter(void) {

	}

}

