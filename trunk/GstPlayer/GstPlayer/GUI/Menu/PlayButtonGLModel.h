/*
 * PlayButtonGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef PLAYBUTTON_H_
#define PLAYBUTTON_H_

#include <GLEngine/Model/IGLModel.h>

namespace gstplayer {

	class PlayButtonGLModel: public gl::IGLModel {
		public:
			PlayButtonGLModel();
			bool leftButtonClicked(const gl::GLVertex& mousePosition);
			virtual ~PlayButtonGLModel();
	};

}

#endif /* PLAYBUTTON_H_ */
