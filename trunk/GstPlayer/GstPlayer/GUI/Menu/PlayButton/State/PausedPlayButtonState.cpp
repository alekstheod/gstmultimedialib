/*
 * PausedPlayButtonState.cpp
 *
 *  Created on: Jul 24, 2011
 *      Author: alekstheod
 */

#include "PausedPlayButtonState.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>

namespace gstplayer {

	const std::string PausedPlayButtonState::CONST_BUTTON_TEXTURE_NAME="play_button_paused.png";

	// load a 256x256 RGB .RAW file as a texture
	GLuint LoadTextureRAW( const char * filename, int wrap )
	{
	    GLuint texture;
	    int width, height;
	    unsigned char * data;
	    FILE * file;

	    // open texture data
	    file = fopen( filename, "rb" );
	    if ( file == NULL ) return 0;

	    // allocate buffer
	    width = 256;
	    height = 256;
	    data = (unsigned char*)malloc( width * height * 3 );

	    // read texture data
	    fread( data, width * height * 3, 1, file );
	    fclose( file );

	    // allocate a texture name
	    glGenTextures( 1, &texture );

	    // select our current texture
	    glBindTexture( GL_TEXTURE_2D, texture );

	    // select modulate to mix texture with color for shading
	    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	    // when texture area is small, bilinear filter the closest mipmap
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	                     GL_LINEAR_MIPMAP_NEAREST );
	    // when texture area is large, bilinear filter the first mipmap
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	    // if wrap is true, the texture wraps over at the edges (repeat)
	    //       ... false, the texture ends at the edges (clamp)
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
	                     wrap ? GL_REPEAT : GL_CLAMP );
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
	                     wrap ? GL_REPEAT : GL_CLAMP );

	    // build our texture mipmaps
	    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
	                       GL_RGB, GL_UNSIGNED_BYTE, data );

	    // free buffer
	    free( data );

	    return texture;
	}

	PausedPlayButtonState::PausedPlayButtonState(const std::string& texturePath)throw(gl::GLException) {
		_texture=LoadTextureRAW("texture.raw",0);
	}


	PausedPlayButtonState::~PausedPlayButtonState() {
		glDeleteTextures(1, &_texture);
	}


	void PausedPlayButtonState::clickButton(PlayButtonGLModel* playButton){

	}


	bool PausedPlayButtonState::drawButton(const APlayButtonState::RECT& buttonRect){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.2f, 0.2f, 0.1f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.2f, 0.0f, 0.1f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.1f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.2f, 0.1f);
		glEnd();
		return true;
	}

}
