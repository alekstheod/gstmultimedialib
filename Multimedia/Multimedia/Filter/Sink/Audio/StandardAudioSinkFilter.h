/*
 * StandardAudioOutputFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef STANDARDAUDIOOUTPUTFILTER_H_
#define STANDARDAUDIOOUTPUTFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia{

	class StandardAudioSinkFilter : public BaseSinkFilter {
	public:
	    static const std::string CONST_PLUGIN_NAME;

	public:
	    StandardAudioSinkFilter(const std::string& description)throw (GstException);
	    virtual ~StandardAudioSinkFilter(void);
	};

}

#endif /* STANDARDAUDIOOUTPUTFILTER_H_ */
