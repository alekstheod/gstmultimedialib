/*
 * IFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef IFILTER_H_
#define IFILTER_H_
#include <gst/gst.h>

namespace multimedia
{

/**
 * Basic filter interface.
 *
 */
class AFilter
{
public:
  AFilter() {}
  virtual bool addToPipeline ( GstElement* pipeline, const std::string& type )
  {
     return false;
  };
  
  virtual bool addToPipeline ( GstElement* pipeline ) = 0;
  virtual ~AFilter() {}
};

}

#endif /* IFILTER_H_ */
