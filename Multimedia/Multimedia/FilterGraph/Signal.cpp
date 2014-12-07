#include "Signal.h"

namespace multimedia{

  bool Signal::apply( GstElement* pipeline, GMainLoop* loop )const
  {
    return applyImpl(pipeline, loop);
  }
  
}