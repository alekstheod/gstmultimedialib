/*
 * Texture.cpp
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#include "Texture.h"

namespace gl {

Texture::Texture( GLuint texture ) {
	_texture=texture;
	glGenTextures(1, &_texture);
}

Texture::~Texture() {
	glDeleteTextures(1, &_texture);
}

void Texture::applyTexture( GLenum target ){
	glBindTexture(target, _texture);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

}
