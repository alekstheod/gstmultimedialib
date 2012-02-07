project(GLEngine)
cmake_minimum_required(VERSION 2.8)

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif (OPENGL_FOUND)

find_package (GLUT REQUIRED)
if (GLUT_FOUND)
  include_directories(${GLUT_INCLUDE_DIRS})
endif (GLUT_FOUND)

include_directories(. ../Utilities)

add_library(GLEngine
	    GLEngine/Camera/ICamera.cpp
	    GLEngine/Camera/SimpleCamera.cpp
	    GLEngine/Light/ILight.cpp
	    GLEngine/Light/WhiteLight.cpp 
	    GLEngine/Model/Wavefront/Model.cpp
		GLEngine/Model/Wavefront/Object.cpp
		GLEngine/Model/ImageTexture.cpp
		GLEngine/Model/IModelFactory.cpp
		GLEngine/Model/ITexture.cpp
		GLEngine/Model/Rotation.cpp
		GLEngine/Model/Texture.cpp
		GLEngine/Model/Vertex.cpp
		GLEngine/Device.cpp
		GLEngine/GLException.cpp)
