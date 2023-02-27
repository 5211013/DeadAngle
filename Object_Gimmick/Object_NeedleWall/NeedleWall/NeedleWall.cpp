//*****************************************************************************
//
// ゲームシーンの針壁のギミック針壁のギミック
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "NeedleWall.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

NeedleWall::NeedleWall()
	: MOVE_LIMIT(3.0f)
	, FINALMOVE_LIMIT(6.7f)
	, m_kind(0)
	, m_bMove(false)
	, m_bMoved(false)
	, m_bFinalMove(false)
	, m_bReturn(false)
{
	m_speed = LoadInitializeText(INITIALIZE_TEXT_GIMMICK, "NeedleWall", "speed"); //針が動く速度で使用 0.01f
}

//初期化
void NeedleWall::Initialize(const int kind, const D3DXVECTOR3 position)
{
	m_kind = kind;

	m_position3D = position;

	//位置を保存
	m_savePos = m_position3D;

	//移動軸
	m_moveAxis = POSITION_Z;

	if (m_moveAxis >= MAX_AXIS)
	{
		m_moveAxis = POSITION_Z;
	}

	//移動する向き
	m_moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

//更新
void NeedleWall::Update()
{
	//移動
	if (m_bMove)
	{
		Move();
	}

	//最後の移動
	if (m_bFinalMove)
	{
		FinalMove();
	}

	//戻る
	if (m_bReturn)
	{
		Return();
	}
}

//描画
void NeedleWall::Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//行列情報更新
	UpdateMatrix(pNormalMap);

	pNormalMap->Draw(pCamera, pProjection, pAmbient, pLight);
}

//種類を取得
int NeedleWall::GetKind() const
{
	return m_kind;
}

//移動フラグ取得
bool NeedleWall::GetMove() const
{
	return m_bMove;
}

//移動し終わったフラグ取得
bool NeedleWall::GetMoved() const
{
	return m_bMoved;
}

//最後の移動フラグ取得
bool NeedleWall::GetFinalMove() const
{
	return m_bFinalMove;
}

//移動フラグ切替
void NeedleWall::ChangeFlagMove(const bool bWhich)
{
	m_bMove = bWhich;
}

//最後の移動フラグ切替
void NeedleWall::ChangeFlagFinalMove(const bool bWhich)
{
	m_bFinalMove = bWhich;
}

//戻るフラグ切替
void NeedleWall::ChangeFlagReturn(const bool bWhich)
{
	m_bReturn = bWhich;
}

/*---------------private関数-------------*/

//移動
void NeedleWall::Move()
{
	//移動量を計算
	const float wMoveLimit = GetPosition(m_savePos) + MOVE_LIMIT;

	if (wMoveLimit - m_speed > GetPosition(m_position3D))
	{
		m_position3D += m_moveDir * m_speed;
	}
	else
	{
		//限界値に設定
		SetPosition(wMoveLimit);

		//移動終了
		m_bMove = false;

		//移動が終わった
		m_bMoved = true;
	}
}

//最後の動き(ゲームオーバー)
void NeedleWall::FinalMove()
{
	//速度変更
	const float speed = m_speed * 20;

	//移動量を計算
	const float wMoveLimit = GetPosition(m_savePos) + FINALMOVE_LIMIT;

	if (wMoveLimit - speed > GetPosition(m_position3D))
	{
		m_position3D += m_moveDir * speed;
	}
	else
	{
		//限界値に設定
		SetPosition(wMoveLimit);

		m_bFinalMove = false;
	}
}

//戻る
void NeedleWall::Return()
{
	if (GetPosition(m_savePos) + m_speed < GetPosition(m_position3D))
	{
		m_position3D -= m_moveDir * m_speed;
	}
	else
	{
		//限界値に設定
		SetPosition(GetPosition(m_savePos));
	}
}

//位置(移動軸によって戻り値を変更する)
float NeedleWall::GetPosition(const D3DXVECTOR3 position)
{
	float wPosition = 0.0f;

	if (m_moveDir == D3DXVECTOR3(1.0f, 0.0f, 0.0f))
	{
		wPosition = position.x;
	}
	else if(m_moveDir == D3DXVECTOR3(0.0f, 1.0f, 0.0f))
	{
		wPosition = position.y;
	}
	else if (m_moveDir == D3DXVECTOR3(0.0f, 0.0f, 1.0f))
	{
		wPosition = position.z;
	}

	return wPosition;
}

//位置をセット（向きによって変わる）
void NeedleWall::SetPosition(const float num)
{
	if (m_moveDir == D3DXVECTOR3(1.0f, 0.0f, 0.0f))
	{
		m_position3D.x = num;
	}
	else if (m_moveDir == D3DXVECTOR3(0.0f, 1.0f, 0.0f))
	{
		m_position3D.y = num;
	}
	else if (m_moveDir == D3DXVECTOR3(0.0f, 0.0f, 1.0f))
	{
		m_position3D.z = num;
	}
}

//行列情報更新
void NeedleWall::UpdateMatrix(NormalMap * pNormalMap)
{
	//スケール変更
	D3DXMatrixScaling(&m_matScale, 1.8f);

	//平行移動行列作成
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	m_matWorld = m_matScale * m_matTrans;

	//ワールド座標行列をセット
	pNormalMap->SetWorldTransform(&m_matWorld);
}