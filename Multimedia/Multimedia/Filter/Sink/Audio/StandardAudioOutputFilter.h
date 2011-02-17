/*
 * StandardAudioOutputFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef STANDARDAUDIOOUTPUTFILTER_H_
#define STANDARDAUDIOOUTPUTFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseOutputFilter.h>

namespace multimedia{

	class StandardAudioOutputFilter : public BaseOutputFilter {
	public:
	    static const std::string CONST_PLUGIN_NAME;
	    static const std::string CONST_PLUGIN_DESCRIPTION;

	public:
	    StandardAudioOutputFilter(void)throw (GstException);
	    virtual ~StandardAudioOutputFilter(void);
	};

}

#endif /* STANDARDAUDIOOUTPUTFILTER_H_ */
