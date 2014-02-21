#ifndef __SHAPE_H
#define __SHAPE_H

#include "../Tools/GLCommon.h"

class CShape
{
protected:
	float* m_pfVertices;
	int m_nNbVertices;
public:
	CShape();
	CShape(CShape const& shape);
	~CShape();

	void SetVertices(float* pfVertices);

	void Draw();
};

#endif //__SHAPE_H