/*
 * APlayButtonState.h
 *
 *  Created on: Jul 22, 2011
 *      Author: alekstheod
 */

#ifndef APLAYBUTTONSTATE_H_
#define APLAYBUTTONSTATE_H_
#include <Utilities/SmartPtr/SmartPtr.h>

namespace gstplayer {

	class PlayButtonGLModel;

	class APlayButtonState {
		protected:
			bool changeState(PlayButtonGLModel* playButton, APlayButtonState* newState);

		public:
			APlayButtonState();
			virtual void clickButton(PlayButtonGLModel* playButton)=0;
			virtual ~APlayButtonState();
	};

}

#endif /* APLAYBUTTONSTATE_H_ */
