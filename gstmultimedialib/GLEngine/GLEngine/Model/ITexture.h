/*
 * ITexture.h
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include <GL/gl.h>

namespace gl {

class ITexture {
public:
	ITexture();
	virtual bool applyTexture( GLenum target )=0;
	virtual ~ITexture();
};

}

#endif /* ITEXTURE_H_ */
