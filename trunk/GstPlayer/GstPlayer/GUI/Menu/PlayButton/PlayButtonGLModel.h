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

namespace gstplayer {

	class APlayButtonState;

	class PlayButtonGLModel: public gl::IGLModel {
		private:
			friend class APlayButtonState;
			utils::SmartPtr<APlayButtonState> _buttonState;

		public:
			inline PlayButtonGLModel(){

			}

			inline bool drawModel(void){

			}

			inline bool leftButtonClicked(const gl::GLVertex& mousePosition){
				return true;
			}

			inline virtual ~PlayButtonGLModel(){

			}
	};

}

#endif /* PLAYBUTTON_H_ */
