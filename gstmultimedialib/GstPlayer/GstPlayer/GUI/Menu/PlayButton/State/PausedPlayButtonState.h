/*
 * PausedPlayButtonState.h
 *
 *  Created on: Jul 24, 2011
 *      Author: alekstheod
 */

#ifndef PAUSEDPLAYBUTTONSTATE_H_
#define PAUSEDPLAYBUTTONSTATE_H_

#include <GstPlayer/GUI/Menu/PlayButton/APlayButtonState.h>
#include <string>
#include <GLEngine/GLException.h>
#include <GL/gl.h>

namespace gstplayer {

class PausedPlayButtonState: public gstplayer::APlayButtonState {
public:
	static const std::string CONST_BUTTON_TEXTURE_NAME;

private:
	GLuint _texture;

public:
	PausedPlayButtonState(const std::string& texturePath)
			throw (gl::GLException);
	void clickButton(PlayButtonModel* playButton);
	bool drawButton(const APlayButtonState::rect& buttonRect);
	virtual ~PausedPlayButtonState();
};

}

#endif /* PAUSEDPLAYBUTTONSTATE_H_ */
