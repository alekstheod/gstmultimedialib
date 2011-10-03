/*
 * MenuGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef MENUGLMODEL_H_
#define MENUGLMODEL_H_
#include <Utilities/SmartPtr/SmartPtr.h>
#include <GLEngine/Model/IModel.h>
#include <GstPlayer/GUI/Menu/PlayButton/PlayButtonModel.h>
#include <GLEngine/GLException.h>

namespace gstplayer{

	class MenuModel : public gl::IModel{
		private:
			utils::SmartPtr<PlayButtonModel> _playButton;

		public:
			MenuModel()throw(gl::GLException);
			bool drawModel(void);
			bool addRotationX(unsigned int rotationId, float angle);
			bool addRotationY(unsigned int rotationId, float angle);
			bool addRotationZ(unsigned int rotationId, float angle);
			bool removeAllRotations();
			void leftButtonClick(const gl::Vertex& mousePosition);
			void rightButtonClick(const gl::Vertex& mousePosition);
			void mouseMoved(const gl::Vertex& oldMousePosition, gl::Vertex& newMousePosition);
			virtual ~MenuModel();
	};

}


#endif /* MENU_H_ */
