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

namespace gstplayer{

	class MenuGLModel : public gl::IGLModel{
		private:
			utils::SmartPtr<PlayButtonGLModel> _playButton;
			utils::SmartPtr<IGLModel> _voiceControl;
			utils::SmartPtr<IGLModel> _playingControl;

		public:
			MenuGLModel();
			bool drawModel(void);
			bool addRotationX(unsigned int rotationId, float angle);
			bool addRotationY(unsigned int rotationId, float angle);
			bool addRotationZ(unsigned int rotationId, float angle);
			bool removeAllRotations();
			bool leftButtonClick(const gl::GLVertex& mousePosition);
			bool rightButtonClick(const gl::GLVertex& mousePosition);
			virtual ~MenuGLModel();
	};

}


#endif /* MENU_H_ */
