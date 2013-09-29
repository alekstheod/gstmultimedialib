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
private:
  virtual bool applyImpl( GLenum target )=0;
  
public:
  ITexture();
  bool apply ( GLenum target );
  virtual ~ITexture();
};

}

#endif /* ITEXTURE_H_ */
