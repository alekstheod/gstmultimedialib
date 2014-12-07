/*
 * BaseOutputFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef AOUTPUTFILTER_H_
#define AOUTPUTFILTER_H_
#include <gst/gst.h>
#include <string>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/GstObject.h>

namespace multimedia
{

class BaseSinkFilter: public AFilter, GstObject
{
private:
    GSmartPtr<GstElement> m_output;

private:
    friend class BaseConverterFilter;
    friend class BaseDecoderFilter;
    friend class SourceFilter;

    template<typename... FilterTypes>
    friend class PlaybinFilterGraph;

private:
    bool addToPipelineImpl ( GstElement* pipeline );

public:
    BaseSinkFilter ( const std::string& pluginName, const std::string& description );

    template<typename ObjectType>
    void setObject ( const gchar *first_property_name, ObjectType obj ) {
        g_object_set ( G_OBJECT ( m_output.getPtr() ), first_property_name, obj, NULL );
    }

    bool addToPipeline ( GstElement* pipeline, const std::string& type );
    virtual ~BaseSinkFilter ( void );
};

}

#endif /* AOUTPUTFILTER_H_ */
