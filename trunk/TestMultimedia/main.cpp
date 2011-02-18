/*
 * main.cpp
 *
 *  Created on: Feb 18, 2011
 *      Author: m1cRo
 */
#include <Multimedia/FilterGraph/Audio/AudioFilterGraph.h>
#include <iostream>

using namespace multimedia;
using namespace std;
int main(int argc, char** argv){
	try{
		gst_init (&argc, &argv);
		AudioFilterGraph graph("file:///windows/D/sample.mp3");
		graph.Play();
		sleep(5000);
	}catch(const GstException& e){
		cout<<e.what()<<endl;
	}
	return 0;
}
