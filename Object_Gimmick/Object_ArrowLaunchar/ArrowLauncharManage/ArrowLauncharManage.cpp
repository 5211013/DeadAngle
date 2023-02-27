//*****************************************************************************
//
// ゲームシーンの矢の発射ギミック
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "ArrowLauncharManage.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

ArrowLauncharManage::ArrowLauncharManage()
	: m_gimmickNo(0)
	, m_checkGimmickNo(-1)
{
}

ArrowLauncharManage::~ArrowLauncharManage()
{
	for (Launchar * pLaunchar : m_vecLaunchar)
	{
		if (pLaunchar)
		{
			delete pLaunchar;
			pLaunchar = nullptr;
		}
	}
	for (Arrow * pArrow : m_vecArrow)
	{
		if (pArrow)
		{
			delete pArrow;
			pArrow = nullptr;
		}
	}
	for (Switch * pSwitch : m_vecSwitch)
	{
		if (pSwitch)
		{
			delete pSwitch;
			pSwitch = nullptr;
		}
	}
}

void ArrowLauncharManage::Initialize(Engine * pEngine, Common::CommonData & gameData)
{
	//m_arrow.Load(pEngine, MODEL_ARROW);
	//m_launchar.Load(pEngine, MODEL_LAUNCHAR);
	//m_floor.Load(pEngine, MODEL_FLOOR);
	//m_switch.Load(pEngine, MODEL_SWITCH);

	//モデル読み込み
	LoadModel(pEngine, &m_arrow, gameData, MODEL_ARROW);
	LoadModel(pEngine, &m_launchar, gameData, MODEL_LAUNCHAR);

	for (int i = 0; i < MAX_PARTS; i++)
	{
		LoadModel(pEngine, &m_switch[i], gameData, MODELS_SWITCH[i]);
	}

	//テキストからロードして初期化(矢と発射口)
	TextLoadInitialize();

	//テキストからロードして初期化(スイッチ)
	SwitchTextLoadInitialize();
}

//更新
void ArrowLauncharManage::Update(Engine * pEngine)
{
	//スイッチ
	for (Switch * pSwitch : m_vecSwitch)
	{
		//デバック用
		if (pEngine->GetKeyState(DIK_B))
		{
			pSwitch->ChangeFlagPush(true);
		}

		pSwitch->Update();
	}
	

	//スイッチ
	for (Switch * pSwitch : m_vecSwitch)
	{
		//矢
		for (Arrow * pArrow : m_vecArrow)
		{
			//ギミック番号が一致しているか
			if (pSwitch->GetGimmickNo() == pArrow->GetGimmickNo()) {

				//同じギミックの番号じゃなければ
				if (m_checkGimmickNo != pSwitch->GetGimmickNo())
				{
					m_checkGimmickNo = pSwitch->GetGimmickNo();

					//発射フラグを調べる
					if (pArrow->GetShoot(pSwitch->GetMove()))
					{
						pArrow->Update();
					}
				}
			}
		}
	}
}

//描画
void ArrowLauncharManage::Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//発射口
	for (Launchar * pLaunchar : m_vecLaunchar)
	{
		pLaunchar->Draw(&m_launchar, pCamera, pProjection, pAmbient, pLight);
	}

	//矢
	for (Arrow * pArrow : m_vecArrow)
	{
		pArrow->Draw(&m_arrow, pCamera, pProjection, pAmbient, pLight);
	}

	//スイッチ
	for (Switch * pSwitch : m_vecSwitch)
	{
		pSwitch->Draw(&m_switch[FLOOR], &m_switch[SWITCH], pCamera, pProjection, pAmbient, pLight);
	}
}

//デバック用
void ArrowLauncharManage::Debug(Engine * pEngine)
{
	for (int i = 0; i < (int)m_vecArrow.size(); i++)
	{
		pEngine->DrawPrintf(0, 500 + i * 20, FONT_GOTHIC20, Color::GREEN, "Pos.x = %.2f, Pos.y = %.2f, Pos.z = %.2f", m_vecArrow[i]->GetPosition3D().x, m_vecArrow[i]->GetPosition3D().y, m_vecArrow[i]->GetPosition3D().z);
		pEngine->DrawPrintf(0, 660 + i * 20, FONT_GOTHIC20, Color::GREEN, "Arrow : bExist = %d", m_vecArrow[i]->GetExist());
	}

	for (int i = 0; i < (int)m_vecArrow.size(); i++)
	{
		pEngine->DrawPrintf(200, 660 + i * 20, FONT_GOTHIC20, Color::GREEN, "Switch : bMove = %d", m_vecSwitch[i]->GetMove());
	}
}

/*---------------private関数---------------*/

//発射口のデータを読み込む
void ArrowLauncharManage::ArrowLauncharDataLoad()
{
	//領域確保
	Launchar * pLaunchar = new Launchar;

	D3DXVECTOR3 wLauncharPos;
	D3DXVECTOR3 wLauncharDir;

	//発射口の座標
	m_ifsArrowLauncharManage >> wLauncharPos.x;
	m_ifsArrowLauncharManage >> wLauncharPos.y;
	m_ifsArrowLauncharManage >> wLauncharPos.z;

	//発射口の向き
	m_ifsArrowLauncharManage >> wLauncharDir.x;
	m_ifsArrowLauncharManage >> wLauncharDir.y;
	m_ifsArrowLauncharManage >> wLauncharDir.z;

	//発射口初期化
	pLaunchar->Initialize(wLauncharPos, wLauncharDir);

	//発射口のvector追加
	m_vecLaunchar.push_back(pLaunchar);

	//矢の初期化
	ArrowDataLoad(wLauncharDir, pLaunchar->GetMatrix());
}

//矢データを読み込む
void ArrowLauncharManage::ArrowDataLoad(const D3DXVECTOR3 launcharDir, const D3DXMATRIX matWorld)
{
	//領域確保
	Arrow * pArrow = new Arrow;

	float wArrowDistance;

	//矢の距離
	m_ifsArrowLauncharManage >> wArrowDistance;

	//矢初期化
	pArrow->Initialize(m_gimmickNo, launcharDir, wArrowDistance, matWorld);

	//矢のvector追加
	m_vecArrow.push_back(pArrow);
}

//スイッチデータを読み込む
void ArrowLauncharManage::SwitchDataLoad()
{
	int wSwitchNum;
	D3DXVECTOR3 wSwitchPos;

	//スイッチの数
	m_ifsArrowLauncharManage >> wSwitchNum;

	//スイッチの数だけ
	for (int i = 0; i < wSwitchNum; i++)
	{
		//領域確保
		Switch * pSwitch = new Switch;

		m_ifsArrowLauncharManage >> wSwitchPos.x;
		m_ifsArrowLauncharManage >> wSwitchPos.y;
		m_ifsArrowLauncharManage >> wSwitchPos.z;

		//スイッチ
		pSwitch->Initialize(wSwitchPos, m_gimmickNo);

		//vector追加
		m_vecSwitch.push_back(pSwitch);
	}
}

//テキストからロードして初期化(矢と発射口)
void ArrowLauncharManage::TextLoadInitialize()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, "ArrowLaunchar", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//領域確保
		Arrow * pArrow = new Arrow;
		Launchar * pLaunchar = new Launchar;

		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		int wGimmickNo;
		D3DXVECTOR3 wPosition;
		D3DXVECTOR3 wDirection;
		float wDistance;

		//ギミックの番号
		wGimmickNo = (int)LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "gimmickNo");

		//位置
		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "posZ");

		//向き
		wDirection.x = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "dirX");
		wDirection.y = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "dirY");
		wDirection.z = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "dirZ");

		//飛距離
		wDistance = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "distance");

		//発射口の初期化
		pLaunchar->Initialize(wPosition, wDirection);

		//vector追加
		m_vecLaunchar.push_back(pLaunchar);

		//矢の初期化
		pArrow->Initialize(wGimmickNo, wDirection, wDistance, pLaunchar->GetMatrix());

		//vector追加
		m_vecArrow.push_back(pArrow);
	}
}

//テキストからロードして初期化(スイッチ)
void ArrowLauncharManage::SwitchTextLoadInitialize()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, "ArrowLaunchar", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		int wGimmickNo;
		int wSwitchNum;
		D3DXVECTOR3 wPosition;

		//ギミック番号
		wGimmickNo = (int)LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, wsNum, "gimmickNo");

		//スイッチの数
		wSwitchNum = (int)LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, "Switch : " + wsNum, "num");

		//スイッチの数だけ繰り返す
		for (int j = 0; j < wSwitchNum; j++)
		{
			//jを文字列に変換
			std::string wsSwitchNum = std::to_string(j);

			//領域確保
			Switch * pSwitch = new Switch;

			wPosition.x = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, "Switch : " + wsNum, "posX" + wsSwitchNum);
			wPosition.y = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, "Switch : " + wsNum, "posY" + wsSwitchNum);
			wPosition.z = LoadInitializeText(INITIALIZE_TEXT_ARROWLAUNCHAR, "Switch : " + wsNum, "posZ" + wsSwitchNum);

			//初期化
			pSwitch->Initialize(wPosition, wGimmickNo);

			//vector追加
			m_vecSwitch.push_back(pSwitch);
		}
	}
}