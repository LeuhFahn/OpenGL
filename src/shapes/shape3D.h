#ifndef __SHAPE3D_H
#define __SHAPE3D_H

#include "shape.h"

class CShape3D : public CShape
{
protected:

public:
	CShape3D();
	CShape3D(CShape3D const& shape);
	~CShape3D();

	virtual void Draw(float fDeltatime);
};

#endif //__SHAPE3D_H