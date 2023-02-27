//*****************************************************************************
//
// ゲームシーンの飛んでくる矢
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

class Arrow : public BaseObject
{
public:

	Arrow();

	//初期化(引数 : 向き、移動距離、発射口のワールド行列)
	void Initialize(const int gimmickNo, const D3DXVECTOR3 direction, const float distance, const D3DXMATRIX matLauncherWorld);

	//更新
	void Update();

	//描画
	void Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//ギミック番号取得
	int GetGimmickNo() const;

	//発射フラグを調べる
	bool GetShoot(const bool bSwitchMove) const;

private:

	//ギミック番号
	int m_gimmickNo;

	//距離
	float m_distance;

	//位置(保存用)
	D3DXVECTOR3 m_savePos;

	//向き
	D3DXVECTOR3 m_direction3D;

	//時間セット用
	bool m_bTimeSet;

	//発射間隔
	IntervalManage m_imShoot;

	//発射タイマーセット
	void ShootTimeSet();

	//移動
	void Move();

	//移動距離を計算
	void MoveDistance();

	//行列情報更新
	void UpdateMatrix(NormalMap * pModel);
};