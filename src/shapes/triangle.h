#ifndef __TRIANGE_H
#define __TRIANGE_H

#include "shape2D.h"

class CTriangle : public CShape2D
{
protected:
    GLuint timeLocation;
	float m_fTime;
public:
	CTriangle();	
	~CTriangle();

	void Draw(float fDeltatime);
};

#endif // __TRIANGE_H