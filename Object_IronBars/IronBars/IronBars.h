//*****************************************************************************
//
// ゲームシーンの右のステージの鉄格子
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\BaseObject\\BaseObject.h"

class IronBars : public BaseObject
{
public:

	IronBars();

	//初期化
	void Initialize(const D3DXVECTOR3 position);

	//更新
	void Update(Engine * pEngine);

	//描画
	void Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//さがるフラグ切替
	void ChangeFlagDown(const bool bWhich);

	//デバック用
	float GetSpeed() const;

	//さがるフラグ取得
	bool GetDown() const;

private:

	//落下する限界
	const float LIMIT_DOWN;

	//さがるときの速度
	const float DOWN_SPEED;

	//あがるときの速度
	const float UP_SPEED;

	//スピードの最大値
	const float MAX_SPEED;

	//高さセーブ用
	float m_saveHight;

	//さがる上限
	float m_limitDown;

	//落下フラグ
	bool m_bDown;

	//動いている用フラグ
	bool m_bMove;

	//さがる
	void Down();

	//あがる
	void Up();

	//速度調整
	void SpeedChange();

	//行列情報更新
	void UpdateMatrix(NormalMap * pModel);
};