//*****************************************************************************
//
// ゲームシーンの石の台に置く石の管理
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "StoneManage.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

StoneManage::StoneManage()
	: STONE_SET_ADJUST(D3DXVECTOR3(0.0f, 1.7f, 0.0f))
{
}

//初期化
void StoneManage::Initialize(Engine * pEngine, Common::CommonData & gameData)
{
	//モデル読み込み
	LoadModel(pEngine, &m_model[STONE], gameData, MODEL_STONE);
	LoadModel(pEngine, &m_model[STONE_SET], gameData, MODEL_STONESET);

	//テキストからデータロード
	TextDataLoad();

	//テキストからデータロード(石の台)
	StoneSetTextDataLoad();
}

//更新
void StoneManage::Update(Engine * pEngine, const D3DXVECTOR3 playerPos)
{
	for (int i = 0; i < MAX_STONE; i++)
	{
		//取得範囲内か
		if (m_stoneSet[i].GetRange())
		{
			//石を持っていなくて且つ石が置いていれば
			if (!m_stone[i].GetHave() && m_stoneSet[i].GetPut())
			{
				//入手
				m_stone[i].ChangeFlagGet(true);

				//石が置いてるフラグ切替
				m_stoneSet[i].ChangeFlagPut(false);
			}
		}
	}

	for (int i = STONE_SET_RIGHT_CENTER; i < MAX_STONESET; i++)
	{
		if (m_stoneSet[i].GetRange())
		{
			for (int j = 0; j < MAX_STONE; j++)
			{
				//石が置いていない且つ石を持っていたら
				if (!m_stoneSet[i].GetPut() && m_stone[j].GetHave())
				{
					//位置更新
					m_stone[j].SetPosition(m_stoneSet[i].GetPosition3D() + STONE_SET_ADJUST);

					//入手フラグ切替
					m_stone[j].ChangeFlagGet(false);

					//石が置いてるフラグ切替
					m_stoneSet[i].ChangeFlagPut(true);
				}
			}
		}
	}
	
	
	//石
	for (int i = 0; i < MAX_STONE; i++)
	{
		m_stone[i].Update();
	}

	//石の台
	for (int i = 0; i < MAX_STONESET; i++)
	{
		m_stoneSet[i].Update(playerPos);
	}
}

//描画
void StoneManage::Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//石
	for (int i = 0; i < MAX_STONE; i++)
	{
		m_stone[i].Draw(&m_model[STONE], pCamera, pProjection, pAmbient, pLight);
	}

	//石の台
	for (int i = 0; i < MAX_STONESET; i++)
	{
		m_stoneSet[i].Draw(&m_model[STONE_SET], pCamera, pProjection, pAmbient, pLight);
	}
}

//デバック用
void StoneManage::Debug(Engine * pEngine)
{
	int work = 400;

	for (int i = 0; i < MAX_STONE; i++)
	{
		pEngine->DrawPrintf(0, work + 20 * i, FONT_GOTHIC20, Color::GREEN, "stone : bHave[%d] : %d", i, m_stone[i].GetHave());
	}

	for (int i = 0; i < MAX_STONESET; i++)
	{
		pEngine->DrawPrintf(0, work + 60 + 20 * i, FONT_GOTHIC20, Color::GREEN, "StoneSet : bPut[%d] : %d", i, m_stoneSet[i].GetPut());
	}
}

/*---------------private関数---------------*/

//テキストからデータロード
void StoneManage::TextDataLoad()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_STONE, "Stone", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		D3DXVECTOR3 wPosition;

		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_STONE, wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_STONE, wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_STONE, wsNum, "posZ");

		//初期化
		m_stone[i].Initialize(wPosition);
	}
}

//テキストからデータロード(石の台)
void StoneManage::StoneSetTextDataLoad()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_STONESET, "StoneSet", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		D3DXVECTOR3 wPosition;
		int wPut;
		bool wbPut;

		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_STONESET, wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_STONESET, wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_STONESET, wsNum, "posZ");

		wPut = (int)LoadInitializeText(INITIALIZE_TEXT_STONESET, wsNum, "bPut");

		if (wPut == 0)
		{
			wbPut = false;
		}
		else
		{
			wbPut = true;
		}
		
		//初期化
		m_stoneSet[i].Initialize(wPosition, wbPut);
	}
}
