/*
 * APlayButtonState.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: alekstheod
 */

#include "APlayButtonState.h"
#include "PlayButtonGLModel.h"

namespace gstplayer {

	APlayButtonState::APlayButtonState() {
	}

	APlayButtonState::~APlayButtonState() {
	}

	bool APlayButtonState::changeState(PlayButtonGLModel* playButton, APlayButtonState* newState){
		if(playButton==NULL || newState==NULL){
			return false;
		}

		playButton->_buttonState.Attach(newState);
		return true;
	}

}