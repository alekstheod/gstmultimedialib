/*
 * Texture.h
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <GL/gl.h>
#include <GL/glu.h>

namespace gl
{

class Texture
{
private:
    friend class Scene;
    GLuint m_texture;

private:
    virtual bool applyImpl ( GLenum target);
    
public:
    Texture ( GLuint texture );
    bool apply( GLenum target );
    virtual ~Texture();
};

}

#endif /* TEXTURE_H_ */
