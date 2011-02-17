//============================================================================
// Name        : MultimediaTest.cpp
// Author      : m1cRo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Multimedia/FilterGraph/Audio/AudioFilterGraph.h>
using namespace std;

using namespace multimedia;

int main(int argc, char** argv) {

	try{
		multimedia::AudioFilterGraph graph("file:///windows/D/sample.mp3");
		graph.Play();
	}catch(multimedia::GstException& e){
		cout<<e.what()<<endl;
	}

	return 0;
}
