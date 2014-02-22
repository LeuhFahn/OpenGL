#ifndef __SHAPE_H
#define __SHAPE_H


#include "../Tools/GLCommon.h"
#include "../Tools/Camera.h"
#include "../Tools/ShaderGLSL.h"

class CShape
{
protected:
	float* m_pfVertices;
	int m_nNbVertices;
	SShaderGLSL m_Shader;
public:
	CShape();
	CShape(CShape const& shape);
	~CShape();

	void SetVertices(float* pfVertices);

	virtual void Draw(float fDeltatime);
};

#endif //__SHAPE_H