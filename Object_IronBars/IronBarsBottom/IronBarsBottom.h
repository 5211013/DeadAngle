//*****************************************************************************
//
// 
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\BaseObject\\BaseObject.h"

class IronBarsBottom : public BaseObject
{
public:

	IronBarsBottom();

	//初期化
	void Initialize(const D3DXVECTOR3 position);

	//描画
	void Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);
	
private:

	//行列情報更新
	void UpdateMatrix(NormalMap * pModel);

};