/*
 * PlayingPlayButtonState.cpp
 *
 *  Created on: Jul 23, 2011
 *      Author: alekstheod
 */

#include "PlayingPlayButtonState.h"

namespace gstplayer {

const std::string PlayingPlayButtonState::CONST_BUTTON_TEXTURE_NAME =
		"play_button_playing.png";

PlayingPlayButtonState::PlayingPlayButtonState(const std::string& texturePath)
		throw (gl::GLException) {
}

PlayingPlayButtonState::~PlayingPlayButtonState() {
}

void PlayingPlayButtonState::clickButton(PlayButtonModel* playButton) {
}

bool PlayingPlayButtonState::drawButton(
		const APlayButtonState::rect& buttonRect) {
	glBegin(GL_QUADS);
	glVertex3f(buttonRect._posX, buttonRect._posY, 0.1f);
	glVertex3f(buttonRect._posX, buttonRect._posY - buttonRect._height, 0.1f);
	glVertex3f(buttonRect._posX - buttonRect._width,
			buttonRect._posY - buttonRect._height, 0.1f);
	glVertex3f(buttonRect._posX - buttonRect._width, buttonRect._posY, 0.1f);
	glEnd();
	return true;
}
}
