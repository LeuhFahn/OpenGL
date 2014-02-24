#ifndef __SHAPE_H
#define __SHAPE_H


#include "../Tools/GLCommon.h"
#include "../Tools/Camera.h"
#include "../Tools/ShaderGLSL.h"

class CShape
{
protected:
	SShaderGLSL m_Shader;
	float* m_pfVertices;
	float* m_pfColors;
	int m_nNbVertices;
public:
	CShape();
	CShape(CShape const& shape);
	~CShape();

	void SetVertices(float* pfVertices);
	void SetColors(float* pfColors);

	virtual void Draw(float fDeltatime) = 0;
};

#endif //__SHAPE_H