/*
 * IFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef IFILTER_H_
#define IFILTER_H_
#include <gst/gst.h>
#include <string>

namespace multimedia
{

/**
 * Basic filter interface.
 *
 */
class AFilter
{
private:
    virtual bool addToPipelineImpl ( GstElement* pipeline ) = 0;
    
public:
  AFilter(){}
  bool addToPipeline( GstElement* pipeline ){
    return addToPipelineImpl(pipeline);
  }
  
  virtual ~AFilter(){}
};

}

#endif /* IFILTER_H_ */
