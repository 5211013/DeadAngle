//*****************************************************************************
//
// ゲームシーンの石を置く台
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "StoneSet.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

StoneSet::StoneSet()
	: GET_RANGE(1.5f)
	, m_bPut(false)
{
}

//初期化
void StoneSet::Initialize(const D3DXVECTOR3 position, const bool bPut)
{
	m_position3D = position;

	m_bPut = bPut;
}

//更新
void StoneSet::Update(const D3DXVECTOR3 playerPos)
{
	//プレイヤー位置代入
	PositionSave(playerPos);
}

//描画
void StoneSet::Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//行列情報更新
	UpdateMatrix(pNormalMap);

	//描画
	pNormalMap->Draw(pCamera, pProjection, pAmbient, pLight);
}

//近くにいる
bool StoneSet::GetRange()
{
	//一定範囲内なら
	if (PlayerDistance() < GET_RANGE)
	{
		return true;
	}

	return false;
}

//置くフラグ取得
bool StoneSet::GetPut() const
{
	return m_bPut;
}

//置くフラグ取得
void StoneSet::ChangeFlagPut(const bool bWhich)
{
	m_bPut = bWhich;
}


/*----------------private関数---------------*/

//プレイヤー位置代入
void StoneSet::PositionSave(const D3DXVECTOR3 playerPos)
{
	m_playerPos = playerPos;
}

//プレイヤーとの距離を計算
float StoneSet::PlayerDistance()
{
	D3DXVECTOR3 wDistance = m_position3D - m_playerPos;

	return D3DXVec3Length(&wDistance);
}

//行列情報更新
void StoneSet::UpdateMatrix(NormalMap * pNormalMap)
{
	//スケール変更
	D3DXMatrixScaling(&m_matScale, 0.5f);

	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	m_matWorld = m_matScale * m_matTrans;

	pNormalMap->SetWorldTransform(&m_matWorld);
}