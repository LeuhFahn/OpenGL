#ifndef __CUBE_H
#define __CUBE_H

#include "shape3D.h"
#define NB_TEXTURES 1

class CCube : public CShape3D
{
protected:

    GLuint timeLocation;
	float m_fTime;

	GLuint projectionLocation;
    GLuint viewLocation;
    GLuint objectLocation;
	GLuint diffuseLocation;

	GLuint m_Vao;
	GLuint m_Vbo[4];
	GLuint m_pTextures[NB_TEXTURES];
public:
	CCube();	
	~CCube();

	void Draw(float fDeltatime);
};

#endif // __TRIANGE_H