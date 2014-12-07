/*
 * MenuGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef MENUGLMODEL_H_
#define MENUGLMODEL_H_
#include <Utilities/Memory/SmartPtr/SharedPtr.h>
#include <GLEngine/Model/Model.h>
#include <GstPlayer/GUI/Menu/PlayButton/PlayButtonModel.h>
#include <GLEngine/GLException.h>

namespace gstplayer
{

class MenuModel: public gl::Model
{
private:
    utils::SharedPtr<PlayButtonModel> _playButton;

private:
    void drawImpl ();
    
public:
    MenuModel() throw ( gl::GLException );
    void leftButtonClick ( const gl::Vertex& mousePosition );
    void rightButtonClick ( const gl::Vertex& mousePosition );
    void mouseMoved ( const gl::Vertex& oldMousePosition,
                      gl::Vertex& newMousePosition );
    virtual ~MenuModel();
};

}

#endif /* MENU_H_ */
