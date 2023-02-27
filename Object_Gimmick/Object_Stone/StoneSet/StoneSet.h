//*****************************************************************************
//
// ゲームシーンの石を置く台
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

class StoneSet : public BaseObject
{
public:

	StoneSet();

	//初期化
	void Initialize(const D3DXVECTOR3 position, const bool put);

	//更新
	void Update(const D3DXVECTOR3 playerPos);

	//描画
	void Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);
	
	//近くにいる
	bool GetRange();

	//置くフラグ取得
	bool GetPut() const;

	//置くフラグ取得
	void ChangeFlagPut(const bool bWhich);

private:

	//取得範囲
	const float GET_RANGE;

	//プレイヤーの位置用
	D3DXVECTOR3 m_playerPos;

	//置くフラグ
	bool m_bPut;

	//プレイヤー位置代入
	void PositionSave(const D3DXVECTOR3 playerPos);

	//プレイヤーとの距離を計算
	float PlayerDistance();

	//行列情報更新
	void UpdateMatrix(NormalMap * pNormalMap);
};