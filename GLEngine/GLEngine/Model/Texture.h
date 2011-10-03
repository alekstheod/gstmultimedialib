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

namespace gl {

class Texture {
private:
	friend class Device;
	GLuint _texture;

public:
	Texture( GLuint texture);
	void applyTexture( GLenum target );
	~Texture();
};

}

#endif /* TEXTURE_H_ */
