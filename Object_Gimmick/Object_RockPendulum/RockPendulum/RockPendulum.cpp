//*****************************************************************************
//
// ゲームシーンの岩の振り子
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "RockPendulum.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

RockPendulum::RockPendulum()
	: MAX_ANGLE(30.0f)
	, m_addAngle(0.0f)
{
	m_speed = LoadInitializeText(INITIALIZE_TEXT_GIMMICK, "RockPendulum", "speed"); //振り子の動く速度で使用
}

//初期化
void RockPendulum::Initialize(const D3DXVECTOR3 position, const int rotAxis)
{
	//位置
	m_position3D = position;

	//回転軸
	m_rotAxis = rotAxis;

	//角度(乱数で初期角度を設定する)
	m_addAngle = (float)(rand() % (int)MAX_ANGLE);

	//BB用
	/*D3DXVECTOR3 max = {  1.0f, -4.9f,  1.0f };
	D3DXVECTOR3 min = { -1.0f, -9.0f, -1.0f };*/
}

//更新
void RockPendulum::Update()
{
	if (m_bExist)
	{
		//揺れる
		Swing();
	}	
}

//描画(専用)
void RockPendulum::Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	if (m_bExist)
	{
		//行列情報更新
		UpdateMatrix(pNormalMap);

		//本体
		pNormalMap->Draw(pCamera, pProjection, pAmbient, pLight);
	}
}

/*---------------private関数---------------*/

//揺れる
void RockPendulum::Swing()
{
	m_angle = sin(m_addAngle) * MAX_ANGLE;

	m_addAngle += D3DXToRadian(m_speed);

	//設定した回転軸の回転を行う
	if (m_rotAxis == ROTATE_X)
	{
		D3DXMatrixRotationX(&m_matRotate, D3DXToRadian(m_angle));
	}
	else if (m_rotAxis == ROTATE_Z)
	{
		D3DXMatrixRotationZ(&m_matRotate, D3DXToRadian(m_angle));
	}
	else
	{
		return;
	}
}

//行列情報更新
void RockPendulum::UpdateMatrix(NormalMap * pNormalMap)
{
	//スケール変更
	D3DXMatrixScaling(&m_matScale, 0.7f);

	//平行移動行列作成
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	//ワールド座標行列作成
	m_matWorld = m_matScale * m_matRotate * m_matTrans;

	//ワールド座標行列セット
	pNormalMap->SetWorldTransform(&m_matWorld);
}