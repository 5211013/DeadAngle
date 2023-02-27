//*****************************************************************************
//
// ゲームシーンの石の台に置く石
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "Stone.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

Stone::Stone()
	: m_bHave(false)
{
}

//初期化
void Stone::Initialize(const D3DXVECTOR3 position)
{
	m_position3D = position;
}

//更新
void Stone::Update()
{
}

//描画
void Stone::Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//入手していなけければ
	if (!m_bHave)
	{
		//行列情報更新
		UpdateMatrix(pNormalMap);

		//描画
		pNormalMap->Draw(pCamera, pProjection, pAmbient, pLight);
	}
}

//入手フラグ取得
bool Stone::GetHave()
{
	return m_bHave;
}

//位置をセット
void Stone::SetPosition(const D3DXVECTOR3 position)
{
	m_position3D = position;
}

//入手フラグ切替
void Stone::ChangeFlagGet(const bool bWhich)
{
	m_bHave = bWhich;
}

/*---------------private関数---------------*/