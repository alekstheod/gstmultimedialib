/*
 * Copyright (c) 2013, <Alexandros Theodoridis> <alekstheod@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <Alexandros Theodoridis> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <Alexandros Theodoridis> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "AssimpModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GLEngine/GLException.h>

namespace gl
{

AssimpModel::AssimpModel ( const std::string& fileName )
{
  Assimp::Importer importer;
  m_scene = importer.ReadFile ( fileName.c_str(), aiProcess_Triangulate );
  if ( !m_scene ) {
      throw GLException("Load model failed");
  }

  for ( unsigned int m_i = 0; m_i < m_scene->mNumMeshes; m_i++ ) {
      const aiMesh* mesh = m_scene->mMeshes[m_i];
      m_vertices.reserve(mesh->mNumVertices*3);
      m_normals.reserve(mesh->mNumVertices*3);
      m_textureVertices.reserve(mesh->mNumVertices*3);
      for ( unsigned int vertex = 0; vertex < mesh->mNumVertices; vertex++ ) {
	  if ( mesh->HasPositions () ) {
	      const aiVector3D* vtx = & ( mesh->mVertices[vertex] );
	      m_vertices.push_back ( vtx->x );
	      m_vertices.push_back ( vtx->y );
	      m_vertices.push_back ( vtx->z );
	  }
	  
	  if ( mesh->HasNormals () ) {
	      const aiVector3D* vn = & ( mesh->mNormals[vertex] );
	      m_normals.push_back ( vn->x );
	      m_normals.push_back ( vn->y );
	      m_normals.push_back ( vn->z );
	  }
	  
	  if ( mesh->HasTextureCoords ( 0 ) ) {
	      const aiVector3D* vt = & ( mesh->mTextureCoords[0][vertex] );
	      m_textureVertices.push_back ( vt->x );
	      m_textureVertices.push_back ( vt->y );
	  }
	  
	  if ( mesh->HasTangentsAndBitangents () ) {
	      // NB: could store/print tangents here
	  }
      }
  }

  importer.FreeScene();
}

AssimpModel::~AssimpModel()
{
}

void AssimpModel::drawImpl()
{
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
  
  unsigned int vao = 0;
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

}
