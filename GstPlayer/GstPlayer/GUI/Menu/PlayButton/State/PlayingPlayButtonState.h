/*
 * PlayingPlayButtonState.h
 *
 *  Created on: Jul 23, 2011
 *      Author: alekstheod
 */

#ifndef PLAYINGPLAYBUTTONSTATE_H_
#define PLAYINGPLAYBUTTONSTATE_H_

#include <GL/gl.h>
#include <GstPlayer/GUI/Menu/PlayButton/APlayButtonState.h>
#include <string>
#include <GLEngine/GLException.h>

namespace gstplayer {

class PlayingPlayButtonState: public APlayButtonState {
public:
	static const std::string CONST_BUTTON_TEXTURE_NAME;

private:
	GLuint _texture;

public:
	PlayingPlayButtonState(const std::string& texturePath)
			throw (gl::GLException);
	void clickButton(PlayButtonModel* playButton);
	bool drawButton(const APlayButtonState::rect& buttonRect);
	virtual ~PlayingPlayButtonState();
};

}

#endif /* PLAYINGPLAYBUTTONSTATE_H_ */
