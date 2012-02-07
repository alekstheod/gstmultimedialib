/*
 * BaseStreamingFilterGraph.cpp
 *
 *  Created on: Jul 11, 2010
 *      Author: m1cRo
 */

#include "BaseStreamingFilterGraph.h"

namespace multimedia {

BaseStreamingFilterGraph::BaseStreamingFilterGraph(const std::string& fileName)
		throw (GstException) :
		BasePlaybinFilterGraph(fileName) {
	// TODO Auto-generated constructor stub

}

BaseStreamingFilterGraph::~BaseStreamingFilterGraph(void) {
	// TODO Auto-generated destructor stub
}

}

