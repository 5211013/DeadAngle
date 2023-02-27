//*****************************************************************************
//
// ゲームシーンの岩の振り子
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

class RockPendulum : public BaseObject
{
public:

	RockPendulum();

	//初期化
	void Initialize(const D3DXVECTOR3 position, const int rotAxis);

	//更新
	void Update();

	//描画(専用)
	void Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

private:

	//回転軸
	enum 
	{
		ROTATE_X,
		ROTATE_Y,
		ROTATE_Z,
	};

	//最大の角度
	const float MAX_ANGLE;

	//加算用角度
	float m_addAngle;

	//回転軸
	int m_rotAxis;

	//揺れる
	void Swing();

	//行列情報更新
	void UpdateMatrix(NormalMap * pNormalMap);
};