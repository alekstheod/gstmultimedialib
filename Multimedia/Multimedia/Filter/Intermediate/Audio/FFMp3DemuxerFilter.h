/*
 * FFMp3DemuxerFilter.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef FFMP3DEMUXER_H_
#define FFMP3DEMUXER_H_
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseDemuxerFilter.h>

namespace multimedia {

	class FFMp3DemuxerFilter: public BaseDemuxerFilter {
		public:
			static const std::string CONST_PLUGIN_NAME;
			static const std::string CONST_PLUGIN_DESCRIPTION;

		public:
			FFMp3DemuxerFilter(void) throw (GstException);
			virtual ~FFMp3DemuxerFilter(void);
	};

}

#endif /* FFMP3DEMUXER_H_ */
