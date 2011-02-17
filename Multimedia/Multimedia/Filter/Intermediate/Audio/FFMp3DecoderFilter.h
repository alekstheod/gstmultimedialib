/*
 * FFMp3DecoderFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef FFMP3DECODERFILTER_H_
#define FFMP3DECODERFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseDecoderFilter.h>

namespace multimedia{

	class FFMp3DecoderFilter : public BaseDecoderFilter {
	public:
	    static const std::string CONST_PLUGIN_NAME;
	    static const std::string CONST_PLUGIN_DESCRIPTION;

	public:
	    FFMp3DecoderFilter(void)throw (GstException);
	    virtual ~FFMp3DecoderFilter(void);
	};

}

#endif /* FFMP3DECODERFILTER_H_ */
