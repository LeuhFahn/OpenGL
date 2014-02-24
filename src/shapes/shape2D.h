#ifndef __SHAPE2D_H
#define __SHAPE2D_H

#include "shape.h";

class CShape2D : public CShape
{
protected:

public:
	CShape2D();
	CShape2D(CShape2D const& shape);
	~CShape2D();

	virtual void Draw(float fDeltatime);
};

#endif //__SHAPE_H