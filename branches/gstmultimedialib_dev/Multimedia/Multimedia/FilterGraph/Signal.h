#ifndef SIGNAL_H
#define SIGNAL_H
#include <gst/gst.h>

namespace multimedia
{

class Signal
{
private:
    virtual bool applyImpl ( GstElement* pipeline, GMainLoop* loop ) const = 0;

public:
    bool apply ( GstElement* pipeline, GMainLoop* loop ) const;
    virtual ~Signal() {}
};

template< GstState state >
class ChangeStateSignal : public Signal
{
private:
    bool applyImpl ( GstElement* pipeline, GMainLoop* loop ) const {
        GstStateChangeReturn ret = gst_element_set_state ( pipeline, state );
        if ( ret == GST_STATE_CHANGE_FAILURE ) {
            return false;
        }

        return true;
    }

public:
    virtual ~ChangeStateSignal() {}
};

class PlaySignal : public ChangeStateSignal<GST_STATE_PLAYING> {};
class PauseSignal : public ChangeStateSignal<GST_STATE_PAUSED> {};
class StopSignal : public ChangeStateSignal<GST_STATE_READY> {};

}

#endif // SIGNAL_H
