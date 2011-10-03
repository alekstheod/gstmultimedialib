/*
 * ImageTexture.cpp
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#include "ImageTexture.h"

namespace gl {

ImageTexture::ImageTexture(GLuint textureId, GLsizei imageWidth, GLsizei imageHeight, GLenum glColor, GLenum pixelType):Texture(textureId){
	_width=imageWidth;
	_height=imageHeight;
	_glColor=glColor;
	_pixelType=pixelType;
}

bool ImageTexture::applyTexture( GLenum target, const std::vector< unsigned char >& imageBuffer ){
	if(imageBuffer.empty()){
		return false;
	}

	Texture::applyTexture(target);
	glTexImage2D ( target, 0, _glColor, _width, _height, 0, _glColor, _pixelType, NULL );
	glTexSubImage2D (target, 0, 0, 0, _width, _height,_glColor, _pixelType, imageBuffer.data());
	return true;
}

ImageTexture::~ImageTexture() {
	// TODO Auto-generated destructor stub
}

}
