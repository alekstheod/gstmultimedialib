/*
 * BaseOutputFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

BaseSinkFilter::BaseSinkFilter(const std::string& pluginName,const std::string& description) : m_output (gst_element_factory_make(pluginName.c_str(), description.c_str()) ){
	if (m_output == NULL) {
		throw GstException(
				"BaseOutputFilter::BaseOutputFilter - create output filter named '"
						+ pluginName + "' failed");
	}
}

bool BaseSinkFilter::addToPipeline(GstElement* pipeline, const std::string& type) {
	bool result = false;
	if ( pipeline != NULL ) {
		g_object_set(G_OBJECT(pipeline), (type+"-sink").c_str(), m_output.getPtr(), NULL);
		result = true;
	}
	
	return result;
}

bool BaseSinkFilter::addToPipelineImpl(GstElement* pipeline)
{
	return false;
}

BaseSinkFilter::~BaseSinkFilter(void) {

}

}

