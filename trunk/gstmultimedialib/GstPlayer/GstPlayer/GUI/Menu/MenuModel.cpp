/*
 * MenuGLModel.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#include "MenuModel.h"

namespace gstplayer
{

MenuModel::MenuModel() throw ( gl::GLException )
{
    _playButton = new PlayButtonModel ( 0.9f, -0.7f, 0.2, 0.15,
                                        "/home/alekstheod" );
}

bool MenuModel::drawImpl()
{
    return _playButton->draw();
}

void MenuModel::leftButtonClick ( const gl::Vertex& mousePosition )
{

}

void MenuModel::rightButtonClick ( const gl::Vertex& mousePosition )
{

}

void MenuModel::mouseMoved ( const gl::Vertex& oldMousePosition,
                             gl::Vertex& newMousePosition )
{
}

MenuModel::~MenuModel()
{

}

}

