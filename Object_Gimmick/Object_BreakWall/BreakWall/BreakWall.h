//*****************************************************************************
//
// ゲームシーンの壊れる壁
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

#include "..\\..\\..\\..\\ShaderObject\\Dissolve\\Dissolve.h"

class BreakWall : public BaseObject
{
public:

	BreakWall();

	//初期化
	void Initialize(Engine * pEngine);

	//更新
	void Update(Engine * pEngine);

	//描画(専用)
	void Draw(Engine * pEngine, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

private:

	//壊れる壁の種類
	enum
	{
		BREAKWALL_STAGE_START,
		BREAKWALL_STAGE_LEFT,
		MAX_BREAKWALL,
	};

	//壁が壊れるまでの回数
	const int BREAK_NUM;

	//ディゾルブの最大値
	const float MAX_DISSOLVE;

	//ディゾルブ用
	float m_dissolveNum;

	//カウント用
	float m_dissolveCount;

	//ディゾルブ用フラグ
	bool m_bDissolve;

	//回転行列
	D3DXMATRIX m_matRotate;

	//モデル
	Dissolve m_model[MAX_BREAKWALL];

	//バウンディングボックス
	BoundingBox m_bb;

	//消える
	void Annihilation();
};