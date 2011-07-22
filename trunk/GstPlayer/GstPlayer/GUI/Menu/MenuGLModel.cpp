/*
 * MenuGLModel.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#include "MenuGLModel.h"

namespace gstplayer{

	MenuGLModel::MenuGLModel() {
		_playButton;
		_voiceControl;
		_playingControl;
	}


	bool MenuGLModel::drawModel(void){
		return true;
	}


	bool MenuGLModel::addRotationX(unsigned int rotationId, float angle){
		return true;
	}

	bool MenuGLModel::addRotationY(unsigned int rotationId, float angle){
		return true;
	}


	bool MenuGLModel::addRotationZ(unsigned int rotationId, float angle){
		return true;
	}


	bool MenuGLModel::removeAllRotations(){
		return true;
	}


	void MenuGLModel::leftButtonClick(const gl::GLVertex& mousePosition){

	}


	void MenuGLModel::rightButtonClick(const gl::GLVertex& mousePosition) {

	}


	void MenuGLModel::mouseMoved(const gl::GLVertex& oldMousePosition, gl::GLVertex& newMousePosition){

	}

	MenuGLModel::~MenuGLModel() {

	}

}

