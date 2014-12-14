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

#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#define GL_GLEXT_PROTOTYPES

#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GLEngine/GLException.h>
#include <assimp/scene.h>
#include <IL/il.h>
#include <boost/range/irange.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

namespace gl
{

AssimpModel::AssimpModel ( const std::string& fileName )
{
    m_scene = m_importer.ReadFile ( fileName.c_str(), aiProcess_Triangulate );
    if ( !m_scene ) {
        throw GLException("Load model failed");
    }

    if (m_scene->HasTextures()) {
        throw GLException("AssimpModel::LoadGLTextures failed");
    }
    
    loadTextures(fileName);
}

AssimpModel::~AssimpModel()
{
}

void AssimpModel::drawImpl()
{
    drawInternal(m_scene->mRootNode);
}

// ----------------------------------------------------------------------------
void set_float4(float f[4], float a, float b, float c, float d)
{
    f[0] = a;
    f[1] = b;
    f[2] = c;
    f[3] = d;
}

void color4_to_float4(const aiColor4D *c, float f[4])
{
    f[0] = c->r;
    f[1] = c->g;
    f[2] = c->b;
    f[3] = c->a;
}

void AssimpModel::applyMaterial(const aiMaterial *mtl)
{
    int texIndex = 0;
    aiString texPath;	//contains filename of texture
    if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
    {
        GLuint& texId = m_textures[texPath.data];
        glBindTexture(GL_TEXTURE_2D, texId);
    }

    float color[4];
    set_float4(color, 0.8f, 0.8f, 0.8f, 1.0f);
    aiColor4D diffuse;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        color4_to_float4(&diffuse, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);

    set_float4(color, 0.0f, 0.0f, 0.0f, 1.0f);
    aiColor4D specular;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        color4_to_float4(&specular, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

    set_float4(color, 0.2f, 0.2f, 0.2f, 1.0f);
    aiColor4D ambient;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        color4_to_float4(&ambient, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

    set_float4(color, 0.0f, 0.0f, 0.0f, 1.0f);
    aiColor4D emission;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
        color4_to_float4(&emission, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);

    float shininess, strength;
    unsigned int max = 1;
    int ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    max = 1;
    int ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
    if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
    else {
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
        set_float4(color, 0.0f, 0.0f, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    }

    max = 1;
    GLenum fill_mode;
    int wireframe;
    if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max)) {
        fill_mode = wireframe ? GL_LINE : GL_FILL;
    } else {
        fill_mode = GL_FILL;
    }

    glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

    max = 1;
    int two_sided;
    if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
}


void AssimpModel::loadTextures(const std::string& model)
{
    for (unsigned int material = 0 ; material < m_scene->mNumMaterials; material++) {
        aiString path;
        unsigned int index = 0;
        while(AI_SUCCESS == m_scene->mMaterials[material]->GetTexture(aiTextureType_DIFFUSE, index, &path)) {
            GLuint& texture = m_textures[path.data];
            glGenTextures(1, &texture );
            boost::filesystem::path modelPath(model);
            std::string basepath =  modelPath.remove_leaf().string();
            std::string fileloc = basepath + path.C_Str();
            ILboolean result = ilLoadImage(fileloc.c_str());
            ILuint imageId;
            ilGenImages(1, &imageId);
            ilBindImage(imageId);
            if (result == AI_SUCCESS) {
                ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             ilGetInteger(IL_IMAGE_BPP),
                             ilGetInteger(IL_IMAGE_WIDTH),
                             ilGetInteger(IL_IMAGE_HEIGHT),
                             0,
                             ilGetInteger(IL_IMAGE_FORMAT),
                             GL_UNSIGNED_BYTE,
                             ilGetData()
			    );
            }

            ilDeleteImages(1, &imageId);
            index++;
        }
    }
}

void AssimpModel::drawInternal(const aiNode* nd)
{
    aiMatrix4x4 matrix = nd->mTransformation;

    // update transform
    aiTransposeMatrix4(&matrix);
    glPushMatrix();
    glMultMatrixf((float*)&matrix);
    
    // draw all meshes assigned to this node
    for (unsigned int n = 0; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = m_scene->mMeshes[nd->mMeshes[n]];
        applyMaterial(m_scene->mMaterials[mesh->mMaterialIndex]);

        if(mesh->mNormals == NULL) {
            glDisable(GL_LIGHTING);
        } else {
            glEnable(GL_LIGHTING);
        }

        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            const struct aiFace* face = &mesh->mFaces[t];
            unsigned int modes[4] = {GL_POLYGON, GL_POINTS, GL_LINES, GL_TRIANGLES};
	    unsigned int index = face->mNumIndices > 3? 0: face->mNumIndices;
            glBegin(modes[face->mNumIndices]);
            for(unsigned int i = 0; i < face->mNumIndices; i++) {
                int index = face->mIndices[i];
                if(mesh->mColors[0] != NULL) {
                    glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                }

                if(mesh->mNormals != NULL) {
                    glNormal3fv(&mesh->mNormals[index].x);
                }

                if(mesh->HasTextureCoords(0)) {
                    glTexCoord3f(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y, mesh->mTextureCoords[0][index].z);
                }

                glNormal3fv(&mesh->mNormals[index].x);
                glVertex3fv(&mesh->mVertices[index].x);
            }

            glEnd();
        }

    }

    // draw all children
    for (unsigned int child = 0; child < nd->mNumChildren; ++child) {
        drawInternal(nd->mChildren[child]);
    }

    glPopMatrix();
}

}
