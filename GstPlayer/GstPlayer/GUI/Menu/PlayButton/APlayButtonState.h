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
		public:
			class RECT{
				private:
					friend class PlayButtonGLModel;
					float _posX;
					float _posY;
					float _width;
					float _height;

				public:
					inline RECT(float posX, float posY, float width, float height){
						_posX=posX;
						_posY=posY;
						_width=width;
						_height=height;
					}
			};

		protected:
			bool changeState(PlayButtonGLModel* playButton, APlayButtonState* newState);

		public:
			APlayButtonState();
			virtual void clickButton(PlayButtonGLModel* playButton)=0;
			virtual bool drawButton(const RECT& buttonRect)=0;
			virtual ~APlayButtonState();
	};

}

#endif /* APLAYBUTTONSTATE_H_ */
