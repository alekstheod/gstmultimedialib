/*
 * PlayingPlayButtonState.cpp
 *
 *  Created on: Jul 23, 2011
 *      Author: alekstheod
 */

#include "PlayingPlayButtonState.h"

namespace gstplayer {

	const std::string PlayingPlayButtonState::CONST_BUTTON_TEXTURE_NAME = "play_button_playing.png";

	PlayingPlayButtonState::PlayingPlayButtonState(const std::string& texturePath)throw(gl::GLException) {
	}


	PlayingPlayButtonState::~PlayingPlayButtonState() {
	}


	void PlayingPlayButtonState::clickButton(PlayButtonGLModel* playButton){
	}


	bool PlayingPlayButtonState::drawButton(const APlayButtonState::RECT& buttonRect){
		glBegin(GL_QUADS);
		glVertex3f(0.2f, 0.2f, 0.1f);
		glVertex3f(0.2f, 0.0f, 0.1f);
		glVertex3f(0.0f, 0.0f, 0.1f);
		glVertex3f(0.0f, 0.2f, 0.1f);
		glEnd();
		return true;
	}
}
