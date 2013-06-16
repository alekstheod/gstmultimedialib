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

namespace multimedia {

    template<typename... FilterTypes>
    class PlaybinFilterGraph: public GstObject, public IPlaybin {
        private:
        GMainLoop* _mainLoop;
        GSmartPtr<GstElement> _pipeline;
        std::tuple<FilterTypes...> _filters;

        public:
        const std::string _uri;
        static const std::string CONST_PLAYBIN_PLUGIN_NAME;
        static const std::string CONST_PLAYBIN_PLUGIN_DESCRIPTION;

        private:
        static GstBusSyncReply gstBusSyncHandle ( GstBus *bus, GstMessage *msg, gpointer data ) {
            PlaybinFilterGraph* _this = ( PlaybinFilterGraph* ) data;

            switch ( GST_MESSAGE_TYPE ( msg ) ) {

            case GST_MESSAGE_EOS: {
                g_main_loop_quit ( _this->_mainLoop );
            }
            break;

            case GST_MESSAGE_ERROR: {
                gchar* debug;
                GError* error;

                gst_message_parse_error ( msg, &error, &debug );
                g_free ( debug );

                g_printerr ( "Error: %s\n", error->message );
                g_error_free ( error );

                g_main_loop_quit ( _this->_mainLoop );
            }
            break;

            default: {
            } break;
            }

            return GST_BUS_PASS;
        }

        PlaybinFilterGraph ( const PlaybinFilterGraph& );
        void insertFilter ( multimedia::AFilter& filter ) {
            filter.addToPipeline ( _pipeline.getPtr() );
        }

        public:
        PlaybinFilterGraph ( const std::string& uri, const FilterTypes&... filters ) throw ( GstException ) :_filters ( filters... ), _uri ( uri ) {
            _mainLoop = g_main_loop_new ( NULL, FALSE );
            if ( _mainLoop == NULL ) {
                throw GstException (
                    "BaseFilterGraph::BaseFilterGraph - Create MainLoop failed" );
            }

            _pipeline = gst_element_factory_make ( CONST_PLAYBIN_PLUGIN_NAME.c_str(),CONST_PLAYBIN_PLUGIN_DESCRIPTION.c_str() );
            if ( _pipeline == NULL ) {
                throw GstException (
                    "BasePlaybinFilterGraph::BasePlaybinFilterGraph - Create pipeline failed" );
            }

            g_object_set ( G_OBJECT ( _pipeline.getPtr() ), "uri", _uri.c_str(), NULL );

            GstBus* bus = gst_pipeline_get_bus ( GST_PIPELINE ( _pipeline.getPtr() ) );
            gst_bus_set_sync_handler ( bus, gstBusSyncHandle, this );
            gst_object_unref ( bus );


            utils::apply ( std::bind ( &PlaybinFilterGraph::insertFilter,  this, std::placeholders::_1 ), _filters );
        }

        bool play ( void ) {
            GstStateChangeReturn ret = gst_element_set_state ( _pipeline.getPtr(),GST_STATE_PLAYING );
            if ( ret == GST_STATE_CHANGE_FAILURE ) {
                return false;
            }

            g_main_loop_run ( _mainLoop );
            return true;
        }

        bool stop ( void ) {
            GstStateChangeReturn ret = gst_element_set_state ( _pipeline.getPtr(), GST_STATE_READY );
            if ( ret == GST_STATE_CHANGE_FAILURE ) {
                return false;
            }

            g_main_loop_quit ( _mainLoop );
            return true;
        }

        bool rewind ( void ) {
            return false;
        }

        ~PlaybinFilterGraph() {
            if ( _mainLoop != NULL ) {
                g_main_loop_unref ( _mainLoop );
            }
        }
    };


    template<typename... FilterTypes>
    const std::string PlaybinFilterGraph<FilterTypes...>::CONST_PLAYBIN_PLUGIN_NAME = "playbin2";

    template<typename... FilterTypes>
    const std::string PlaybinFilterGraph<FilterTypes...>::CONST_PLAYBIN_PLUGIN_DESCRIPTION = "Player";

}


#endif /* BASEPLAYBINFILTERGRAPH_H_ */





