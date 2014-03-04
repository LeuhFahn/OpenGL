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
	GLuint sqrtNbInstanceLocation;

	GLuint m_Vao;
	GLuint m_Vbo[4];
	GLuint m_pTextures[NB_TEXTURES];

	const int m_nNbInstance;
public:
	CCube(int nNbInstance = 1);
	~CCube();

	void Draw(float fDeltatime);
};

#endif // __TRIANGE_H