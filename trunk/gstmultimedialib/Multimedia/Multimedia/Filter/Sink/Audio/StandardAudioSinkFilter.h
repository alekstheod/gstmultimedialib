/*
 * StandardAudioOutputFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef STANDARDAUDIOOUTPUTFILTER_H_
#define STANDARDAUDIOOUTPUTFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>

namespace multimedia
{

class StandardAudioSinkFilter : public AFilter
{
private:
    BaseSinkFilter _baseSink;

public:
    static const std::string CONST_PLUGIN_NAME;
    static const std::string CONST_SINK_TYPE;

private:
    bool addToPipelineImpl ( GstElement* pipeline )final;

public:
    StandardAudioSinkFilter ( const std::string& description ) throw ( GstException );
    virtual ~StandardAudioSinkFilter ( void );
};

}

#endif /* STANDARDAUDIOOUTPUTFILTER_H_ */
