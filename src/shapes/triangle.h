#ifndef __TRIANGE_H
#define __TRIANGE_H

#include "shape.h"

class CTriangle : public CShape
{
protected:
	GLuint projectionLocation;
    GLuint viewLocation;
    GLuint objectLocation;
    GLuint timeLocation;
	float m_fTime;
public:
	CTriangle();	
	~CTriangle();

	void Draw(float fDeltatime);
};

#endif // __TRIANGE_H