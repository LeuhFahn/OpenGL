#ifndef __CUBE_H
#define __CUBE_H

#include "shape3D.h"

class CCube : public CShape3D
{
protected:

    GLuint timeLocation;
	float m_fTime;

	GLuint m_Vao;
	GLuint m_Vbo[4];
public:
	CCube();	
	~CCube();

	void Draw(float fDeltatime);
};

#endif // __TRIANGE_H