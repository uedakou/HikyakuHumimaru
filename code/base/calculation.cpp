//============================================
//
// �v�Z�p[calculation.h]
// Author:Uedakou
// 
//============================================
#include "calculation.h"
//***************************************
// �v�Z�p��`
//***************************************


//***************************************
// �v�Z�p����
//***************************************
float RadianToAngle(float fRad)
{
	return(360.0f / (D3DX_PI * 2)) * fRad;
}

float AngleToRadian(float fAngle)
{
	return(D3DX_PI * 2 / 360.0f) * fAngle;
}
