//*****************************************************************************
//
// ゲームシーンのスイッチ
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

class Switch : public BaseObject
{
public:

	Switch();

	//初期化(引数 : 座標, ギミック番号)
	void Initialize(const D3DXVECTOR3 position, const int gimmickNo = 0);

	//更新
	void Update();

	//更新(戻らない)
	void UpdateNeedleWall();

	//描画(専用)
	void Draw(NormalMap * pFloor, NormalMap * pSwitch, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//ギミック番号取得
	int GetGimmickNo() const;

	//移動フラグ取得
	bool GetMove() const;

	//押すフラグ取得
	bool GetPush() const;

	//戻るフラグ取得
	bool GetReturn() const;

	//スイッチを押すプラグ変更
	void ChangeFlagPush(const bool bWhich);

	//スイッチが戻るフラグ変更
	void ChangeFlagReturn(const bool bWhich);
	
private:

	//押す幅の限界
	const float PUSH_LIMIT;

	//ギミック番号
	int m_gimmickNo;

	//スイッチの床部分の座標
	D3DXVECTOR3 m_floorPos;

	//スイッチの座標セーブ用
	D3DXVECTOR3 m_savePos;

	//ボタンが押されているか
	bool m_bPush;

	//戻っているか
	bool m_bReturn;
	
	//動いているか
	bool m_bMove;

	//タイマーセット用
	bool m_bTimeSet;

	//スイッチ用
	IntervalManage m_imPushSwitch;

	//押す
	void Push();

	//戻る
	void Return();

	//戻るまでの時間計測
	void ReturnTimer();

	//行列情報を更新
	void UpdateMatrix(NormalMap * pNormalMap, D3DXVECTOR3 position);
};