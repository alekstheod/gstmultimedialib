/*
 * main.cpp
 *
 *  Created on: Feb 18, 2011
 *      Author: m1cRo
 */
#include <Multimedia/FilterGraph/Video/XVideoFilterGraph.h>
#include <iostream>

using namespace multimedia;
using namespace std;
int main(int argc, char** argv){
	try{
		gst_init (&argc, &argv);
		XVideoFilterGraph graph("file:///home/alekstheod/Downloads/battle/test.avi");
		graph.play();
		gst_deinit();
	}catch(const GstException& e){
		cout<<e.what()<<endl;
	}

	return 0;
}
