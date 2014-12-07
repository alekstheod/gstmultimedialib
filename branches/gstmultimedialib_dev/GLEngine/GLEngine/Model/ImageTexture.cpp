/*
 * ImageTexture.cpp
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#include "ImageTexture.h"

namespace gl
{

ImageTexture::ImageTexture ( GLuint textureId, GLsizei imageWidth,
                             GLsizei imageHeight, GLenum glColor, GLenum pixelType, const std::vector<unsigned char>& imageBuffer ) :
    Texture ( textureId ),m_width ( imageWidth ), m_height ( imageHeight ), m_glColor ( glColor ), m_pixelType ( pixelType ), m_imageBuffer ( imageBuffer )
{
    m_width = imageWidth;
    m_height = imageHeight;
    m_glColor = glColor;
    m_pixelType = pixelType;
}

bool ImageTexture::applyImpl ( GLenum target )
{
    if ( m_imageBuffer.empty() ) {
        return false;
    }

    glTexImage2D ( target, 0, m_glColor, m_width, m_height, 0, m_glColor, m_pixelType,NULL );
    glTexSubImage2D ( target, 0, 0, 0, m_width, m_height, m_glColor, m_pixelType,m_imageBuffer.data() );
    return true;
}

ImageTexture::~ImageTexture() {}

}
