//*****************************************************************************
//
// ゲームシーンの飛んでくる矢
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "Arrow.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

Arrow::Arrow()
	: m_distance(0.0f)
	, m_savePos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_direction3D(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_bTimeSet(false)
{
	m_speed = LoadInitializeText(INITIALIZE_TEXT_GIMMICK, "Arrow", "speed"); //矢の速度で使用
	m_bExist = false;
}

//初期化(生成用)
void Arrow::Initialize(const int gimmickNo, const D3DXVECTOR3 direction, const float distance, const D3DXMATRIX matLauncherWorld)
{
	//座標
	m_position3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ギミック番号
	m_gimmickNo = gimmickNo;

	//向き
	m_direction3D = direction;

	//距離を保存
	m_distance = distance;

	//発射口の行列を保存
	m_matWorld = matLauncherWorld;

	//位置を保存しておく
	m_savePos = m_position3D;
}

//更新
void Arrow::Update()
{
	//発射タイマーセット
	ShootTimeSet();

	//移動
	Move();

	//移動距離を計算
	MoveDistance();
}

//描画
void Arrow::Draw(NormalMap * pModel, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	if (m_bExist)
	{
		//行列情報の更新
		UpdateMatrix(pModel);

		//描画
		pModel->Draw(pCamera, pProjection, pAmbient, pLight);
	}
}

//ギミックの番号取得
int Arrow::GetGimmickNo() const
{
	return m_gimmickNo;
}

//発射フラグを調べる
bool Arrow::GetShoot(const bool bSwitchMove) const
{
	if (bSwitchMove)
	{
		return true;
	}
	else
	{
		if (!m_bExist)
		{
			return false;
		}
		return true;
	}
}

/*---------------private関数---------------*/

//発射タイマーセット
void Arrow::ShootTimeSet()
{
	//タイマーセットしていなければ
	if (!m_bTimeSet) {
		m_imShoot.SetInterval(1300);

		m_bExist = true;
		m_bTimeSet = true;
	}
}

//移動
void Arrow::Move()
{
	//設定した向きに進む
	m_position3D += m_direction3D * m_speed;
}

//移動距離を計算
void Arrow::MoveDistance()
{
	//進んでる距離を計算
	D3DXVECTOR3 travelDistance = m_position3D - m_savePos;

	//長さを求める
	float wLength = D3DXVec3Length(&travelDistance);

	//設定した移動距離と実際の移動距離を比べる
	if (wLength > m_distance)
	{
		m_bExist = false;

		//設定した時間を超えたら
		if (m_imShoot.GetTiming())
		{
			//スタート地点に戻る
			m_position3D = m_savePos;

			//フラグリセット
			m_bTimeSet = false;
		}
	}
}

//行列情報更新
void Arrow::UpdateMatrix(NormalMap * pModel)
{
	//行列設定
	D3DXMatrixTranslation(&m_matTrans, &m_position3D);

	//スケール変更
	D3DXMatrixScaling(&m_matScale, 0.45f);

	//ワールド座標計算
	D3DXMATRIX matWorld = m_matScale * m_matWorld * m_matTrans;

	//ワールド座標セット
	pModel->SetWorldTransform(&matWorld);
}