/*
 * WhiteGLLight.cpp
 *
 *  Created on: May 20, 2011
 *      Author: m1cRo
 */

#include "WhiteGLLight.h"
#include <GL/gl.h>


namespace gl {

	WhiteGLLight::WhiteGLLight() {
		// TODO Auto-generated constructor stub

	}

	WhiteGLLight::~WhiteGLLight() {
		// TODO Auto-generated destructor stub
	}

	bool WhiteGLLight::applyLight(){
        GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
        GLfloat mat_shininess[]={50.0};
        GLfloat light_position[]={-5.0,5.0,5.0,0.0};
        GLfloat white_light[]={1.0,1.0,1.0,1.0};
        glClearColor(0.0,0.0,0.0,0.0);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
        glLightfv(GL_LIGHT0,GL_POSITION,light_position);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
        glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
        return true;
	}

}
