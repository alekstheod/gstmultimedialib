/*
 * MenuGLModel.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#include "MenuGLModel.h"

namespace gstplayer{

	MenuGLModel::MenuGLModel()throw(gl::GLException) {
		_playButton=new PlayButtonGLModel(0.9f , -0.7f , 0.2, 0.15,"/home/alekstheod");
	}


	bool MenuGLModel::drawModel(void){
		_playButton->drawModel();
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

