/*
 * BasePlayBinFilterGraph.h
 *
 *  Created on: Jul 3, 2010
 *      Author: m1cro
 */

#ifndef BASEPLAYBINFILTERGRAPH_H_
#define BASEPLAYBINFILTERGRAPH_H_

#include <string>
#include <tuple>
#include <functional>
#include <Utilities/MPL/Tuple.h>
#include <gst/gst.h>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/GstObject.h>
#include <Utilities/Design/Factory.h>
#include <Multimedia/FilterGraph/IPlaybin.h>
#include <Multimedia/Filter/Source/SourceFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseEncoderFilter.h>
#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <Multimedia/FilterGraph/Signal.h>

namespace multimedia {
  
template<typename... FilterTypes>
class PlaybinFilterGraph: public GstObject, public IPlaybin {
private:
    GMainLoop* m_mainLoop;
    GSmartPtr<GstElement> m_pipeline;
    std::tuple<FilterTypes...> m_filters;

public:
    static const std::string CONST_PLAYBIN_PLUGIN_NAME;
    static const std::string CONST_PLAYBIN_PLUGIN_DESCRIPTION;

private:
    static GstBusSyncReply gstBusSyncHandle ( GstBus *bus, GstMessage *msg, gpointer data ) {
        PlaybinFilterGraph* _this = ( PlaybinFilterGraph* ) data;

        switch ( GST_MESSAGE_TYPE ( msg ) ) {
        case GST_MESSAGE_ERROR: {
            gchar* debug;
            GError* error;

            gst_message_parse_error ( msg, &error, &debug );
            g_free ( debug );

            g_printerr ( "Error: %s\n", error->message );
            g_error_free ( error );

            g_main_loop_quit ( _this->m_mainLoop );
        }
        break;

        default: {
        } break;
        }

        return GST_BUS_PASS;
    }

public:
    PlaybinFilterGraph(const FilterTypes&... filters ) :m_filters ( filters... ){
        m_mainLoop = g_main_loop_new ( NULL, FALSE );
        if ( m_mainLoop == NULL ) {
            throw GstException (
                "BaseFilterGraph::BaseFilterGraph - Create MainLoop failed" );
        }

        m_pipeline = gst_element_factory_make ( CONST_PLAYBIN_PLUGIN_NAME.c_str(),CONST_PLAYBIN_PLUGIN_DESCRIPTION.c_str() );
        if ( m_pipeline == NULL ) {
            throw GstException (
                "BasePlaybinFilterGraph::BasePlaybinFilterGraph - Create pipeline failed" );
        }

        GstBus* bus = gst_pipeline_get_bus ( GST_PIPELINE ( m_pipeline.getPtr() ) );
        gst_bus_set_sync_handler ( bus, gstBusSyncHandle, this );
        gst_object_unref ( bus );

        std::for_each( m_filters, [this](multimedia::AFilter& filter ){
	  filter.addToPipeline ( this->m_pipeline.getPtr() ); 
	} );
    }
    
    PlaybinFilterGraph ( const std::string& uri, const FilterTypes&... filters ) : PlaybinFilterGraph(filters...){
        g_object_set ( G_OBJECT ( m_pipeline.getPtr() ), "uri", uri.c_str(), NULL );
    }

    bool sendSignal( const Signal& signal )
    {
	return signal.apply( m_pipeline.getPtr(), m_mainLoop  );
    }

    ~PlaybinFilterGraph() {
        if ( m_mainLoop != NULL ) {
	    g_main_loop_quit ( m_mainLoop );
            g_main_loop_unref ( m_mainLoop );
        }
    }
};

template<typename... FilterTypes>
const std::string PlaybinFilterGraph<FilterTypes...>::CONST_PLAYBIN_PLUGIN_NAME = "playbin2";

template<typename... FilterTypes>
const std::string PlaybinFilterGraph<FilterTypes...>::CONST_PLAYBIN_PLUGIN_DESCRIPTION = "Player";

}


#endif /* BASEPLAYBINFILTERGRAPH_H_ */





