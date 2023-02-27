//*****************************************************************************
//
// ゲームシーンの壊れる壁
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "BreakWall.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

BreakWall::BreakWall()
	: BREAK_NUM(3)
	, MAX_DISSOLVE(1.0f)
	, m_dissolveNum(0.0f)
	, m_dissolveCount(0.0f)
	, m_bDissolve(false)
{
	m_speed = LoadInitializeText(INITIALIZE_TEXT_GIMMICK, "BreakWall", "speed"); //ディゾルブの値変更に使用

	m_bExist = true;
}

//初期化
void BreakWall::Initialize(Engine * pEngine)
{
	//位置
	m_position3D = { 0.0f, 0.0f, 0.0f };

	//スケール変更
	D3DXMatrixScaling(&m_matScale, 1.8f);

	//180度回転
	D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(180.0f));

	//行列設定
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	//ワールド座標変換
	m_matWorld = m_matScale * m_matTrans;

	//モデル読み込み
	for (int i = 0; i < MAX_BREAKWALL; i++)
	{
		m_model[i].Load(pEngine, MODELS_BREAKWALL[i], TEXTURE_SHADER_BLENDMASK1);
		m_model[i].SetWorldTransform(&m_matWorld);
	}
}

//更新
void BreakWall::Update(Engine * pEngine)
{
	if (m_bExist)
	{
		//デバック用
		if (pEngine->GetKeyStateSync(DIK_N))
		{
			m_bDissolve = true;
		}

		//消える
		Annihilation();
	}
}

//描画(専用)
void BreakWall::Draw(Engine * pEngine, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	if (m_bExist)
	{
		for (int i = 0; i < MAX_BREAKWALL; i++)
		{
			m_model[i].Draw(pCamera, pProjection, pAmbient, pLight);
		}
	}
}


/*---------------private関数-------------*/

//消える
void BreakWall::Annihilation()
{
	if (m_bDissolve)
	{
		if (MAX_DISSOLVE - m_speed > m_dissolveNum)
		{
			m_dissolveNum += m_speed;
		}
		else {
			m_bExist = false;
			m_bDissolve = false;
		}

		//ディゾルブ値をセット
		for (int i = 0; i < MAX_BREAKWALL; i++)
		{
			m_model[i].SetDissolveNum(m_dissolveNum);
		}
	}

	//回数分けてに消える(一応残している)

		////ディゾルブ値をセット
		//m_dissolve.SetDissolveNum(m_dissolveNum);

		////最大値を超えているか
		//if (MAX_DISSOLVE - m_speed > m_dissolveNum)
		//{
		//	//１回の消滅で消える量(全体の数値を壊れるまでの回数で除算)
		//	const float amount = MAX_DISSOLVE / BREAK_NUM;

		//	//1回で消える量を超えているか
		//	if (amount - m_speed > m_dissolveCount)
		//	{
		//		m_dissolveCount += m_speed;
		//		m_dissolveNum += m_speed;
		//	}
		//	else
		//	{
		//		//達していない分を計算
		//		float work = amount - m_dissolveCount;

		//		m_dissolveNum += work;

		//		//カウンターをリセット
		//		m_dissolveCount = 0.0f;

		//		//フラグをリセット
		//		m_bDissolve = false;
		//	}
		//}
		//else{
		//	m_bExist = false;
		//}
}
