//*****************************************************************************
//
// 鉄格子の管理
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "IronBarsManage.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

IronBarsManage::IronBarsManage()
	: DOWN_RANGE(1.5f)
{
}

//初期化
void IronBarsManage::Initialize(Engine * pEngine, Common::CommonData & gameData)
{
	//モデル読み込み
	LoadModel(pEngine, &m_model[IRONBARS], gameData, MODEL_IRONBARS);
	LoadModel(pEngine, &m_model[BOTTOM], gameData, MODEL_IRONBARS_BOTTOM);
	

	//テキストからロードして初期化
	TextLoadInitialize();
}

//更新
void IronBarsManage::Update(Engine * pEngine, const D3DXVECTOR3 playerPos,const bool bNeedleWallClear)
{
	//プレイヤーが範囲内に入ったら
	if (DownRange(playerPos))
	{
		for (int i = 0; i < MAX_NUM; i++)
		{
			//さがっていなければ
			if (!m_ironBars[i].GetDown())
			{
				m_ironBars[i].ChangeFlagDown(true);
			}
		}
	}

	//針の壁をクリアしたら
	if (bNeedleWallClear)
	{
		for (int i = 0; i < MAX_NUM; i++)
		{
			m_ironBars[i].ChangeFlagDown(false);
		}
	}


	for (int i = 0; i < MAX_NUM; i++)
	{
		m_ironBars[i].Update(pEngine);
	}
}

//描画
void IronBarsManage::Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		m_ironBars[i].Draw(&m_model[IRONBARS], pCamera, pProjection, pAmbient, pLight);

		m_ironBarsBottom[i].Draw(&m_model[BOTTOM], pCamera, pProjection, pAmbient, pLight);
	}
}

//デバッグ用
void IronBarsManage::Debug(Engine * pEngine)
{
	pEngine->DrawPrintf(0, 420, FONT_GOTHIC20, Color::GREEN, "鉄の柵のspeed : %.2f", m_ironBars[0].GetSpeed());

	pEngine->DrawPrintf(0, 440, FONT_GOTHIC20, Color::GREEN, "鉄の柵のY : %.2f", m_ironBars[0].GetPosition3D().y);

	pEngine->DrawPrintf(0, 520, FONT_GOTHIC20, Color::GREEN, "bDown: %d", m_ironBars[0].GetDown());
}


/*---------------private関数--------------*/

//テキストからロードして初期化
void IronBarsManage::TextLoadInitialize()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_IRONBARS, "IronBars", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		D3DXVECTOR3 wPosition;

		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_IRONBARS, wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_IRONBARS, wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_IRONBARS, wsNum, "posZ");

		//初期化
		m_ironBars[i].Initialize(wPosition);


		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_IRONBARS, wsNum, "BottomPosX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_IRONBARS, wsNum, "BottomPosY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_IRONBARS, wsNum, "BottomPosZ");

		//初期化
		m_ironBarsBottom[i].Initialize(wPosition);
	}
}

//プレイヤーとの距離
bool IronBarsManage::DownRange(const D3DXVECTOR3 playerPos)
{
	//鉄格子と鉄格子の間を求める
	D3DXVECTOR3 wPosition = m_ironBarsBottom[EXIT].GetPosition3D() - m_ironBarsBottom[ENTRANCE].GetPosition3D();

	//真ん中を求める
	wPosition = wPosition / 2 + m_ironBarsBottom[ENTRANCE].GetPosition3D();

	//2点のベクトルを求める
	D3DXVECTOR3 wDistance = wPosition - playerPos;

	//距離を求める
	float distance = D3DXVec3Length(&wDistance);

	//一定以内であれば
	if (distance < DOWN_RANGE)
	{
		return true;
	}

	return false;
}
