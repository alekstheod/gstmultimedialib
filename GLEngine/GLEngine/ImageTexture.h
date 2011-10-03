/*
 * ImageTexture.h
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

#include "Texture.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

namespace gl {

class ImageTexture: public gl::Texture {
private:
	GLsizei _width;
	GLsizei _height;
	GLenum _glColor;
	GLenum _pixelType;

public:
	ImageTexture(GLuint textureId, GLsizei imageWidth, GLsizei imageHeight, GLenum glColor, GLenum pixelType);
	bool applyTexture( GLenum target, const std::vector< unsigned char >& imageBuffer );
	virtual ~ImageTexture();
};

}

#endif /* IMAGETEXTURE_H_ */
