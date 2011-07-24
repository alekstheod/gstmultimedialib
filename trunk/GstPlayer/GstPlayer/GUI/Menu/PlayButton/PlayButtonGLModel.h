/*
 * PlayButtonGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef PLAYBUTTONGLMODULE_H_
#define PLAYBUTTONGLMODULE_H_

#include <GLEngine/Model/IGLModel.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Utilities/SmartPtr/SmartPtr.h>
#include <GstPlayer/GUI/Menu/PlayButton/State/PausedPlayButtonState.h>
#include <GLEngine/GLException.h>

namespace gstplayer {

	class APlayButtonState;

	/*
	 * PlayButtonGLModel represent the play button on GstPlayer menu.
	 * This class contain inline methods in order to prevent linker errors
	 * in case of SmartPtr<T> using with the T = APlayButtonState.
	 */
	class PlayButtonGLModel: public gl::IGLModel {
		private:
			friend class APlayButtonState;
			utils::SmartPtr<APlayButtonState> _buttonState;
			std::string _menuTexturesPath;
			APlayButtonState::RECT _rect;

		public:
			inline PlayButtonGLModel(float posX, float posY, float width, float height, const std::string& texturesPath)throw(gl::GLException):_rect(posX, posY, width, height){
				_buttonState=new PausedPlayButtonState(texturesPath+"/"+PausedPlayButtonState::CONST_BUTTON_TEXTURE_NAME);
				if(_buttonState==NULL){
					//ToDo throw exception.
				}

				_menuTexturesPath=texturesPath;
			}

			inline bool leftButtonClicked(const gl::GLVertex& mousePosition){
				return true;
			}

			inline virtual ~PlayButtonGLModel(){

			}

			inline bool drawModel(void){
				return _buttonState->drawButton(_rect);
			}


			inline bool addRotationX(unsigned int rotationId, float angle){
				return true;
			}


			inline bool addRotationY(unsigned int rotationId, float angle){
				return true;
			}


			inline bool addRotationZ(unsigned int rotationId, float angle){
				return true;
			}


			inline bool removeAllRotations(){
				return true;
			}
	};

}

#endif /* PLAYBUTTON_H_ */
