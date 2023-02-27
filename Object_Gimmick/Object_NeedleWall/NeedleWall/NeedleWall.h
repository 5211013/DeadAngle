//*****************************************************************************
//
//　ゲームシーンの針壁のギミック
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"


class NeedleWall : public BaseObject
{
public:

	NeedleWall();

	//初期化
	void Initialize(const int kind, const D3DXVECTOR3 position);

	//更新
	void Update();

	//描画
	void Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//種類
	int GetKind() const;

	//移動フラグ取得
	bool GetMove() const;

	//移動し終わったフラグ取得
	bool GetMoved() const;

	//最後の移動フラグ取得
	bool GetFinalMove() const;

	//移動フラグ切替
	void ChangeFlagMove(const bool bWhich);

	//最後の移動フラグ切替
	void ChangeFlagFinalMove(const bool bWhich);

	//戻るフラグ切替
	void ChangeFlagReturn(const bool bWhich);

private:

	//向き
	enum 
	{
		POSITION_X,
		POSITION_Y,
		POSITION_Z,
		MAX_AXIS,
	};

	//移動量の限界
	const float MOVE_LIMIT;
	const float FINALMOVE_LIMIT;

	//種類
	int m_kind;

	//移動軸
	int m_moveAxis;

	//位置保存用
	D3DXVECTOR3 m_savePos;

	//移動する向き
	D3DXVECTOR3 m_moveDir;

	//移動用
	bool m_bMove;

	//移動し終わった
	bool m_bMoved;

	//ゲームオーバー
	bool m_bFinalMove;

	//戻る
	bool m_bReturn;

	//移動
	void Move();

	//最後の動き(ゲームオーバー)
	void FinalMove();

	//戻る
	void Return();

	//位置
	float GetPosition(const D3DXVECTOR3 position);

	//位置をセット（向きによって変わる）
	void SetPosition(const float num);

	//行列情報更新
	void UpdateMatrix(NormalMap * pNormalMap);
};