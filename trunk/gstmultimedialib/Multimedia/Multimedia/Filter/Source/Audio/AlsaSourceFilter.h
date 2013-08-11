/*
 * AlsaSourceFilter.h
 *
 *  Created on: Jul 11, 2010
 *      Author: m1cRo
 */

#ifndef ALSASOURCEFILTER_H_
#define ALSASOURCEFILTER_H_
#include <Multimedia/GstException.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>

namespace multimedia {

class AlsaSourceFilter : public AFilter  {
private:
	GSmartPtr<GstElement> _alsaSource;

private:
	friend class BaseFilterGraph;
	friend class BasePlaybinFilterGraph;

public:
	static const std::string CONST_PLUGIN_NAME;

public:
	AlsaSourceFilter(const std::string& pluginDescription);
	virtual ~AlsaSourceFilter(void);
};

}

#endif /* ALSASOURCEFILTER_H_ */
