/*
 * APlayButtonState.h
 *
 *  Created on: Jul 22, 2011
 *      Author: alekstheod
 */

#ifndef APLAYBUTTONSTATE_H_
#define APLAYBUTTONSTATE_H_
#include <Utilities/Memory/SmartPtr/SharedPtr.h>

namespace gstplayer {

class PlayButtonModel;

class APlayButtonState {
public:
	class RECT {
	public:
		RECT() {
		}
		friend class PlayButtonModel;
		float _posX;
		float _posY;
		float _width;
		float _height;

	public:
		inline RECT(float posX, float posY, float width, float height) {
			_posX = posX;
			_posY = posY;
			_width = width;
			_height = height;
		}
	};

protected:
	bool changeState(PlayButtonModel* playButton, APlayButtonState* newState);

public:
	APlayButtonState();
	virtual void clickButton(PlayButtonModel* playButton)=0;
	virtual bool drawButton(const RECT& buttonRect)=0;
	virtual ~APlayButtonState();
};

}

#endif /* APLAYBUTTONSTATE_H_ */
