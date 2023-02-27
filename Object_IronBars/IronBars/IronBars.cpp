//*****************************************************************************
//
// ゲームシーンの右のステージの鉄格子
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "IronBars.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

IronBars::IronBars()
	: LIMIT_DOWN(7.15f)
	, DOWN_SPEED(0.01f)
	, UP_SPEED(0.001f)
	, MAX_SPEED(0.3f)
	, m_bDown(false)
	, m_bMove(false)
{
	m_speed = 0.01f; //柵が下がる速度で使用　0.01f
}

//初期化
void IronBars::Initialize(const D3DXVECTOR3 position)
{
	m_position3D = position;
	
	//高さを保存
	m_saveHight = m_position3D.y;

	//スケール変更
	D3DXMatrixScaling(&m_matScale, 1.8f);

	//回転
	D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(90.0f));
}

//更新
void IronBars::Update(Engine * pEngine)
{
	if (m_bExist)
	{
		if (pEngine->GetKeyState(DIK_P))
		{
			m_bDown = false;
		}

		if (pEngine->GetKeyState(DIK_O))
		{
			m_bDown = true;
		}

		//あがる
		Up();

		//さがる
		Down();

		//速度変更
		SpeedChange();
	}
}

//描画
void IronBars::Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//行列情報更新
	UpdateMatrix(pModel);

	//描画
	pModel->Draw(pCamera, pProjection, pAmbient, pLight);
}

//さがるフラグ切替
void IronBars::ChangeFlagDown(const bool bWhich)
{
	m_bDown = bWhich;
}

//デバック用
float IronBars::GetSpeed() const
{
	return m_speed;
}

bool IronBars::GetDown() const
{
	return m_bDown;
}

/*---------------private関数---------------*/

//下がる
void IronBars::Down()
{
	//移動量を求める
	const float wMoveLimit = m_saveHight - LIMIT_DOWN;

	if (m_bDown)
	{
		if (m_position3D.y > wMoveLimit + m_speed)
		{
			m_position3D.y -= m_speed;
			
			//動いている
			m_bMove = true;
		}
		else
		{
			//限界値に設定
			m_position3D.y = wMoveLimit;

			//動き終わった
			m_bMove = false;
		}
	}
}

//戻る
void IronBars::Up()
{
	if (!m_bDown)
	{
		if (m_position3D.y < m_saveHight - m_speed)
		{
			m_position3D.y += m_speed;

			//動いている
			m_bMove = true;
		}
		else
		{
			//元の位置に戻る
			m_position3D.y = m_saveHight;

			//動き終わった
			m_bMove = false;
		}
	}
}

//速度調整
void IronBars::SpeedChange()
{
	float wAddSpeed = 0.0f;

	//さがる時とあがる時で初期速度を変える
	if (m_bDown)
	{
		wAddSpeed = DOWN_SPEED;
	}
	else
	{
		wAddSpeed = UP_SPEED;
	}

	//動いていたら
	if (m_bMove)
	{
		m_speed += wAddSpeed;

		//速度の最大値を超えたか
		if (m_speed > MAX_SPEED)
		{
			//上限に設定
			m_speed = MAX_SPEED;
		}
	}
	else
	{
		//元に戻す
		m_speed = 0.0f;
	}
}

//行列情報更新
void IronBars::UpdateMatrix(NormalMap * pModel)
{
	//平行移動行列
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	m_matWorld = m_matScale * m_matRotate * m_matTrans;

	pModel->SetWorldTransform(&m_matWorld);
}