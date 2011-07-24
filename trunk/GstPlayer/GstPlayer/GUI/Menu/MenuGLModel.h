/*
 * MenuGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef MENUGLMODEL_H_
#define MENUGLMODEL_H_
#include <Utilities/SmartPtr/SmartPtr.h>
#include <GLEngine/Model/IGLModel.h>
#include <GstPlayer/GUI/Menu/PlayButton/PlayButtonGLModel.h>
#include <GLEngine/GLException.h>

namespace gstplayer{

	class MenuGLModel : public gl::IGLModel{
		private:
			utils::SmartPtr<PlayButtonGLModel> _playButton;

		public:
			MenuGLModel()throw(gl::GLException);
			bool drawModel(void);
			bool addRotationX(unsigned int rotationId, float angle);
			bool addRotationY(unsigned int rotationId, float angle);
			bool addRotationZ(unsigned int rotationId, float angle);
			bool removeAllRotations();
			void leftButtonClick(const gl::GLVertex& mousePosition);
			void rightButtonClick(const gl::GLVertex& mousePosition);
			void mouseMoved(const gl::GLVertex& oldMousePosition, gl::GLVertex& newMousePosition);
			virtual ~MenuGLModel();
	};

}


#endif /* MENU_H_ */
