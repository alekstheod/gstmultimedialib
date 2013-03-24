/*
 * PlayButtonGLModel.h
 *
 *  Created on: Jul 16, 2011
 *      Author: alekstheod
 */

#ifndef PLAYBUTTONGLMODULE_H_
#define PLAYBUTTONGLMODULE_H_

#include <GLEngine/Model/IModel.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Utilities/Memory/SmartPtr/SharedPtr.h>
#include <GstPlayer/GUI/Menu/PlayButton/State/PausedPlayButtonState.h>
#include <GLEngine/GLException.h>

namespace gstplayer {

class APlayButtonState;

/*
 * PlayButtonModel represent the play button on GstPlayer menu.
 * This class contain inline methods in order to prevent linker errors
 * in case of SharedPtr<T> using with the T = APlayButtonState.
 */
class PlayButtonModel: public gl::IModel {
private:
    friend class APlayButtonState;
    utils::SharedPtr<APlayButtonState> _buttonState;
    std::string _menuTexturesPath;
    APlayButtonState::rect _rect;

public:
    inline PlayButtonModel(float posX, float posY, float width, float height,
                           const std::string& texturesPath) throw (gl::GLException) :
        _rect(posX, posY, width, height) {
        _buttonState = new PausedPlayButtonState(
            texturesPath + "/"
            + PausedPlayButtonState::CONST_BUTTON_TEXTURE_NAME);
        if (_buttonState != NULL ) {
            //ToDo throw exception.
        }

        _menuTexturesPath = texturesPath;
    }

    inline bool leftButtonClicked(const gl::Vertex& mousePosition) {
        return true;
    }

    inline virtual ~PlayButtonModel() {

    }

    inline bool drawModel(void) {
        return _buttonState->drawButton(_rect);
    }

    inline bool addRotationX(unsigned int rotationId, float angle) {
        return true;
    }

    inline bool addRotationY(unsigned int rotationId, float angle) {
        return true;
    }

    inline bool addRotationZ(unsigned int rotationId, float angle) {
        return true;
    }

    inline bool removeAllRotations() {
        return true;
    }
};

}

#endif /* PLAYBUTTON_H_ */
