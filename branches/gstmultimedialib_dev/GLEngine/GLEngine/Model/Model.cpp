#include <GLEngine/Model/Model.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace gl{

Model::~Model(){
  
}

void Model::draw(){
  glTranslatef(m_point.x, m_point.y, m_point.z);
  glRotatef(m_rotation.angle, m_rotation.x, m_rotation.y, m_rotation.z);
  drawImpl();
}

void Model::move( const Vertex& offset ){
  m_point = Vertex(m_point.x + offset.x, 
		   m_point.y + offset.y, 
		   m_point.z + offset.z);
}

void Model::rotate( const Rotation& rotation ){
  m_rotation = Rotation( m_rotation.angle + rotation.angle, 
			 m_rotation.x + rotation.x, 
			 m_rotation.y + rotation.y, 
			 m_rotation.z + rotation.z );
}

}