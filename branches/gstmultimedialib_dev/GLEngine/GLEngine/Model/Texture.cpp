/*
 * Texture.cpp
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#include "Texture.h"

namespace gl
{

Texture::Texture () : m_texture(0)
{
    glGenTextures ( 1, &m_texture );
}

Texture::~Texture()
{
    glDeleteTextures ( 1, &m_texture );
}

bool Texture::applyImpl ( GLenum target){
  return true;
}

bool Texture::apply ( GLenum target )
{
  glEnable ( target );
  glBindTexture ( target, m_texture );
  glTexParameteri ( target, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri ( target, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  return applyImpl(target);
}

}
