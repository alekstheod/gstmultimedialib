/*
 * BaseConverterFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseConverterFilter.h"

namespace multimedia {

BaseConverterFilter::BaseConverterFilter(const std::string& pluginName,
        const std::string& description) throw (GstException) : m_converter ( gst_element_factory_make( pluginName.c_str(), description.c_str() ) ) {
    if (m_converter == NULL) {
        throw GstException(
            "BaseConverterFilter::BaseConverterFilter - create converter filter named '"
            + pluginName + "' failed");
    }
}

bool BaseConverterFilter::connect(BaseSinkFilter* outputFilter) {
    if (outputFilter == NULL) {
        return false;
    }

    return gst_element_link(m_converter.getPtr(), outputFilter->m_output.getPtr());
}

bool BaseConverterFilter::addToPipeline(GstElement* pipeline) {
    if (pipeline == NULL) {
        return false;
    }

    return gst_bin_add(GST_BIN(pipeline), m_converter.getPtr());
}

BaseConverterFilter::~BaseConverterFilter(void) {

}

}

