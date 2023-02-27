//*****************************************************************************
//
//  ゲームシーンの振り子の管理
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "RockPendulumManage.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

RockPendulumManage::RockPendulumManage()
{
}

RockPendulumManage::~RockPendulumManage()
{
	for (RockPendulum * pRockPendulum : m_vecRockPendulum)
	{
		if (pRockPendulum)
		{
			delete pRockPendulum;
			pRockPendulum = nullptr;
		}
	}
}

//初期化
void RockPendulumManage::Initialize(Engine * pEngine, Common::CommonData & gameData)
{
	//モデル読み込み
	LoadModel(pEngine, &m_rockPendulum, gameData, MODEL_ROCK_PENDULUM);

	//テキストからロードして初期化
	TextLoadInitialize();
}

//更新
void RockPendulumManage::Update()
{
	for (RockPendulum * pRockPendulum : m_vecRockPendulum)
	{
		pRockPendulum->Update();
	}
}

//描画
void RockPendulumManage::Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	for (RockPendulum * pRockPendulum : m_vecRockPendulum)
	{
		pRockPendulum->Draw(&m_rockPendulum, pCamera, pProjection, pAmbient, pLight);
	}
}

//テキストからロードして初期化
void RockPendulumManage::TextLoadInitialize()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_ROCKPENDULUM, "RockPendulum", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//領域確保
		RockPendulum * pWork = new RockPendulum;

		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		D3DXVECTOR3 wPosition;
		int wRotAxis;

		//位置
		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_ROCKPENDULUM, wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_ROCKPENDULUM, wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_ROCKPENDULUM, wsNum, "posZ");

		//回転軸
		wRotAxis = (int)LoadInitializeText(INITIALIZE_TEXT_ROCKPENDULUM, wsNum, "RotAxis");

		//初期化
		pWork->Initialize(wPosition, wRotAxis);
		
		//vectorに追加
		m_vecRockPendulum.push_back(pWork);
	}
}
