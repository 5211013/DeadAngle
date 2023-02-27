//*****************************************************************************
//
// ゲームシーンの矢がでる発射口
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "Launchar.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

Launchar::Launchar()
{
}

//初期化
void Launchar::Initialize(const D3DXVECTOR3 position, const D3DXVECTOR3 direction)
{
	//位置設定
	m_position3D = position;

	//向き設定
	m_direction3D = direction;

	//平行移動を行列設定
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	//向きによって回転
	Rotate();

	//行列設定
	m_matWorld = m_matRotate *  m_matTrans;
}

//描画
void Launchar::Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	if (m_bExist)
	{
		//行列情報更新
		UpdateMatrix(pModel);

		//描画
		pModel->Draw(pCamera, pProjection, pAmbient, pLight);
	}
}

//行列取得
D3DXMATRIX Launchar::GetMatrix() const
{
	return m_matWorld;
}

/*---------------private関数---------------*/

//行列情報更新
void Launchar::UpdateMatrix(NormalMap * pModel)
{
	//平行移動
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	//スケール変更
	D3DXMatrixScaling(&m_matScale, 0.15f);

	//行列設定
	m_matWorld = m_matScale * m_matRotate * m_matTrans;

	//ワールド行列セット
	pModel->SetWorldTransform(&m_matWorld);
}

//回転
void Launchar::Rotate()
{
	//向きによって回転させる

	if (m_direction3D.x > 0.0f)
	{
		m_angle = 270.0f;
	}
	else if (m_direction3D.x < 0.0f)
	{
		m_angle = 90.0f;
	}
	else if (m_direction3D.z > 0.0f)
	{
		m_angle = 180.0f;
	}
	else if (m_direction3D.z < 0.0f)
	{
		m_angle = 0.0f;
	}

	D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(m_angle));
}