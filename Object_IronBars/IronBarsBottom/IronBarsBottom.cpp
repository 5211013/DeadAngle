//*****************************************************************************
//
// 
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "IronBarsBottom.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

IronBarsBottom::IronBarsBottom()
{
}

//初期化
void IronBarsBottom::Initialize(const D3DXVECTOR3 position)
{
	m_position3D = position;

	//スケール変更
	D3DXMatrixScaling(&m_matScale, 1.8f);

	//平行移動行列作成
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	//回転
	D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(90.0f));
}

//描画
void IronBarsBottom::Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//行列情報更新
	UpdateMatrix(pModel);

	//描画
	pModel->Draw(pCamera, pProjection, pAmbient, pLight);
}


/*---------------private関数---------------*/

//行列情報更新
void IronBarsBottom::UpdateMatrix(NormalMap * pModel)
{
	//ワールド座標行列作成
	m_matWorld = m_matScale * m_matRotate * m_matTrans;

	//ワールド座標行列セット
	pModel->SetWorldTransform(&m_matWorld);
}