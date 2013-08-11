/*
 * SourceFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Source/SourceFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

const std::string SourceFilter::CONST_PLUGIN_NAME = "filesrc";

SourceFilter::SourceFilter(const std::string& fileName) {
    if (fileName.empty()) {
        throw GstException("SourceFilter::SourceFilter - Empty fileName");
    }
    _source = gst_element_factory_make(CONST_PLUGIN_NAME.c_str(),
                                       fileName.c_str());
    if (_source == NULL) {
        throw GstException(
            "SourceFilter::SourceFilter - File source create failed");
    }

    g_object_set(G_OBJECT(_source.getPtr()), "location", fileName.c_str(),
                 NULL);
}

bool SourceFilter::addToPipeline(GstElement* pipeline) {
    if (pipeline == NULL) {
        return false;
    }

    return gst_bin_add(GST_BIN(pipeline), _source.getPtr());
}

bool SourceFilter::Connect(BaseDemuxerFilter* demuxer) {
    if (demuxer == NULL) {
        return false;
    }

    gst_object_ref(static_cast<GstElement*>(_source.getPtr()));
    return gst_element_link(_source.getPtr(), demuxer->_demuxer.getPtr());
}

bool SourceFilter::Connect(BaseSinkFilter* output) {
    if (output == NULL) {
        return false;
    }

    gst_object_ref(static_cast<GstElement*>(_source.getPtr()));
    return gst_element_link(_source.getPtr(), output->_output.getPtr());
}

SourceFilter::~SourceFilter(void) {

}

}

