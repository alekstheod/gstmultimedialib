/*
 * ITexture.cpp
 *
 *  Created on: Oct 3, 2011
 *      Author: alekstheod
 */

#include "ITexture.h"

namespace gl
{

ITexture::ITexture()
{
    // TODO Auto-generated constructor stub

}

bool ITexture::apply ( GLenum target )
{
    return applyImpl ( target );
}

ITexture::~ITexture()
{
    // TODO Auto-generated destructor stub
}

}
