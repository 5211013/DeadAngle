//*****************************************************************************
//
// ゲームシーンの矢がでる発射口
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

class Launchar : public BaseObject
{
public:

	Launchar();

	//初期化
	void Initialize(const D3DXVECTOR3 position, const D3DXVECTOR3 direction);

	//描画
	void Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//行列取得
	D3DXMATRIX GetMatrix() const;

private:

	//向き
	D3DXVECTOR3 m_direction3D;

	//行列情報更新
	void UpdateMatrix(NormalMap * pModel);

	//向きによって回転
	void Rotate();
};