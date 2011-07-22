/*
 * PlayButtonGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef PLAYBUTTON_H_
#define PLAYBUTTON_H_

#include <GLEngine/Model/IGLModel.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace gstplayer {

	class PlayButtonGLModel: public gl::IGLModel {
		private:
			GLuint _texture;

		public:
			PlayButtonGLModel();
			bool drawModel(void);
			bool leftButtonClicked(const gl::GLVertex& mousePosition);
			virtual ~PlayButtonGLModel();
	};

}

#endif /* PLAYBUTTON_H_ */
