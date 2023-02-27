//*****************************************************************************
//
// ゲームシーンのスイッチ
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "Switch.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

Switch::Switch()
	: PUSH_LIMIT(0.05f)//-0.05
	, m_bPush(false)
	, m_bReturn(false)
	, m_bMove(false)
	, m_bTimeSet(false)
{
	m_speed = LoadInitializeText(INITIALIZE_TEXT_GIMMICK, "Switch", "speed"); //スイッチが動く速度で使用

	m_bExist = true;
}

//初期化
void Switch::Initialize(const D3DXVECTOR3 position, const int gimmickNo)
{
	//ギミック番号
	m_gimmickNo = gimmickNo;

	//位置
	//スイッチ部分
	m_position3D = position;
	
	//床部分
	m_floorPos = m_position3D;

	//スイッチの座標を保存しておく
	m_savePos = m_position3D;
}

//更新
void Switch::Update()
{
	if (m_bExist)
	{	
		//スイッチを押す
		Push();

		//戻るまでの時間計測
		ReturnTimer();

		//スイッチが戻る
		Return();
	}
}

//更新(勝手に戻らない)
void Switch::UpdateNeedleWall()
{
	if (m_bExist)
	{
		//スイッチを押す
		Push();

		//スイッチが戻る
		Return();
	}
}


//描画(専用)
void Switch::Draw(NormalMap * pFloor, NormalMap * pSwitch, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	if (m_bExist)
	{
		//行列情報更新
		UpdateMatrix(pFloor, m_floorPos);
		UpdateMatrix(pSwitch, m_position3D);

		//描画
		pFloor->Draw(pCamera, pProjection, pAmbient, pLight);
		pSwitch->Draw(pCamera, pProjection, pAmbient, pLight);
	}
}

//ギミック番号取得
int Switch::GetGimmickNo() const
{
	return m_gimmickNo;
}

//移動フラグ取得
bool Switch::GetMove() const
{
	return m_bMove;
}

//押すフラグ取得
bool Switch::GetPush() const
{
	return m_bPush;
}

//戻るフラグ取得
bool Switch::GetReturn() const
{
	return m_bReturn;
}

//スイッチを押すプラグ変更
void Switch::ChangeFlagPush(const bool bWhich)
{
	if (bWhich)
	{
		m_bPush = true;
	}
	else
	{
		m_bPush = false;
	}
}

//スイッチが戻るフラグ変更
void Switch::ChangeFlagReturn(const bool bWhich)
{
	if (bWhich)
	{
		m_bReturn = true;
	}
	else
	{
		m_bReturn = false;
	}
}

/*---------------private関数---------------*/

//押す
void Switch::Push()
{
	//スイッチの位置から移動上限を求める
	float wPushLimit = m_savePos.y - PUSH_LIMIT;

	//押されたら
	if (m_bPush)
	{
		//動き始めた
		m_bMove = true;

		//下に動く
		if (m_position3D.y > wPushLimit + m_speed)
		{
			m_position3D.y -= m_speed;
		}
		else
		{
			//上限設定
			m_position3D.y = wPushLimit;

			if (!m_bTimeSet)
			{
				//タイマーセット
				m_imPushSwitch.SetInterval(3000);

				m_bTimeSet = true;
			}
		}
	}
}

//戻る
void Switch::Return()
{
	if (m_bReturn)
	{
		//上に動く
		if (m_position3D.y < m_savePos.y - m_speed)
		{
			m_position3D.y += m_speed;
		}
		else
		{
			//元の位置に戻る
			m_position3D.y = m_savePos.y;

			//フラグを戻す
			m_bReturn = false;
			m_bMove = false;
			m_bTimeSet = false;
		}
	}
}

//戻るまでの時間計測
void Switch::ReturnTimer()
{
	//時間が経過すれば
	if (m_imPushSwitch.GetTiming())
	{
		//フラグを切替
		m_bReturn = true;

		//フラグを戻す
		m_bPush = false;
	}
}

//行列情報を更新
void Switch::UpdateMatrix(NormalMap * pNormalMap, D3DXVECTOR3 position)
{
	//平行移動行列作成
	D3DXMatrixTranslation(&m_matTrans, &position);

	//スケール変更
	D3DXMatrixScaling(&m_matScale, 0.85f);

	//ワールド座標作成
	m_matWorld = m_matScale * m_matTrans;

	//ワールド座標にセット
	pNormalMap->SetWorldTransform(&m_matWorld);
}
