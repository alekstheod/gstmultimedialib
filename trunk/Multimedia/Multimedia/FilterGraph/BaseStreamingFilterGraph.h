/*
 * BaseStreamingFilterGraph.h
 *
 *  Created on: Jul 11, 2010
 *      Author: m1cRo
 */

#ifndef BASESTREAMINGFILTERGRAPH_H_
#define BASESTREAMINGFILTERGRAPH_H_

#include "BasePlaybinFilterGraph.h"

namespace multimedia {

class BaseStreamingFilterGraph: public BasePlaybinFilterGraph {
private:

public:
	BaseStreamingFilterGraph(const std::string& fileName) throw (GstException);
	virtual ~BaseStreamingFilterGraph(void);
};

}

#endif /* BASESTREAMINGFILTERGRAPH_H_ */
