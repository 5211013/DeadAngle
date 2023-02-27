//*****************************************************************************
//
// 針の壁のギミックの管理
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "NeedleWallManage.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

NeedleWallManage::NeedleWallManage()
	: m_moveIndex(0)
	, m_checkIndex(0)
	, m_bCheck(false)
	, m_bClear(false)
	, m_bGameOver(false)
	, m_bTimeSet(false)
{
}

NeedleWallManage::~NeedleWallManage()
{
	for (NeedleWall * pNeedleWall : m_vecNeedleWall)
	{
		if (pNeedleWall)
		{
			delete pNeedleWall;
			pNeedleWall = nullptr;
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

//初期化
void NeedleWallManage::Initialize(Engine * pEngine, Common::CommonData & gameData)
{
	//モデル読み込み
	//針の壁
	for (int i = 0; i < MAX_KIND; i++)
	{
		LoadModel(pEngine, &m_needleWall[i], gameData, MODELS_NEEDLEWALL[i]);
	}

	//スイッチ
	for (int i = 0; i < MAX_SWITCH_PARTS; i++)
	{
		LoadModel(pEngine, &m_switch[i], gameData, MODELS_SWITCH[i]);
	}

	//テキストからロードして初期化
	TextLoadInitialize();

	//テキストからロードして初期化(スイッチ)
	SwitchTextLoadInitialize();

	//テキストからギミックの正しい順番を読み込む
	for (int i = 0; i < (int)m_vecSwitch.size(); i++)
	{
		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		int wGimmick;

		//種類
		wGimmick = (int)LoadInitializeText(INITIALIZE_TEXT_GIMMICK, "NeedleWallManage", "gimmick" + wsNum);

		//vectorに追加
		m_vecGimmick.push_back(wGimmick);
	}
}

//更新
void NeedleWallManage::Update(Engine * pEngine)
{
	//チェックしていない且つクリアしてない且つゲームオーバーでなければ
	if (!m_bCheck && !m_bClear && !m_bGameOver)
	{
		//踏んだスイッチの順番をセーブ
		PushSwitchSave(pEngine);
	}

	//チェック中か
	if (m_bCheck)
	{
		//ギミックのパスワードと入力をチェックする
		CheckGimmickPassward();
	}

	//ゲームオーバーか
	if (m_bGameOver)
	{
		//最後の動き
		FinalMove();
	}

	//クリアしたか
	if (m_bClear)
	{
		//針の壁を戻す
		Return();
	}

	//スイッチ
	for (Switch * pSwitch : m_vecSwitch)
	{
		pSwitch->UpdateNeedleWall();
	}

	//針壁
	for (NeedleWall * pNeedleWall : m_vecNeedleWall)
	{
		pNeedleWall->Update();
	}
}

//描画
void NeedleWallManage::Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight)
{
	//針の壁
	for (int i = 0; i < (int)m_vecNeedleWall.size(); i++)
	{
		//針の種類によって描画するモデルを決める
		m_vecNeedleWall[i]->Draw(&m_needleWall[m_vecNeedleWall[i]->GetKind()], pCamera, pProjection, pAmbient, pLight);
	}

	//スイッチ
	for (Switch * pSwitch : m_vecSwitch)
	{
		pSwitch->Draw(&m_switch[FLOOR], &m_switch[SWITCH], pCamera, pProjection, pAmbient, pLight);
	}
}

//クリアフラグ取得
bool NeedleWallManage::GetClear() const
{
	return m_bClear;
}

//デバック用
void NeedleWallManage::Debug(Engine * pEngine)
{
	/*for (int i = 0; i < (int)m_vecSwitch.size(); i++)
	{
		pEngine->DrawPrintf(0, 400 + i * 20, FONT_GOTHIC20, Color::GREEN, "bPush[%d] : %d", i, m_vecSwitch[i]->GetPush());
	}

	for (int i = 0; i < (int)m_vecSwitch.size(); i++)
	{
		pEngine->DrawPrintf(0, 520 + i * 20, FONT_GOTHIC20, Color::GREEN, "bReturn[%d] : %d", i, m_vecSwitch[i]->GetReturn());
	}*/

	pEngine->DrawPrintf(0, 660, FONT_GOTHIC20, Color::GREEN, "vecPushSwitch.size : %d", m_vecPushSwitch.size());
	pEngine->DrawPrintf(0, 680, FONT_GOTHIC20, Color::GREEN, "bCheck : %d", m_bCheck);

	
	pEngine->DrawPrintf(0, 700, FONT_GOTHIC20, Color::GREEN, "checkIndex : %d", m_checkIndex);
	pEngine->DrawPrintf(0, 720, FONT_GOTHIC20, Color::GREEN, "moveIndex : %d", m_moveIndex);

	pEngine->DrawPrintf(0, 760, FONT_GOTHIC20, Color::GREEN, "bClear : %d", m_bClear);
	pEngine->DrawPrintf(0, 780, FONT_GOTHIC20, Color::GREEN, "bGameOver : %d", m_bGameOver);


	for (int i = 0; i < (int)m_vecNeedleWall.size(); i++)
	{
		pEngine->DrawPrintf(0, 820 + i * 20, FONT_GOTHIC20, Color::GREEN, "bMove[%d] : %d", i ,m_vecNeedleWall[i]->GetMove());
	}

	for (int i = 0; i < (int)m_vecNeedleWall.size(); i++)
	{
		pEngine->DrawPrintf(0, 940 + i * 20, FONT_GOTHIC20, Color::GREEN, "bMoved[%d] : %d", i, m_vecNeedleWall[i]->GetMoved());
	}

	for (int i = 0; i < (int)m_vecNeedleWall.size(); i++)
	{
		pEngine->DrawPrintf(0, 400 + i * 20, FONT_GOTHIC20, Color::GREEN, "bFinalMove[%d] : %d", i, m_vecNeedleWall[i]->GetFinalMove());
	}
}

/*---------------private関数---------------*/

//テキストからロードして初期化
void NeedleWallManage::TextLoadInitialize()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, "NeedleWall", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		//領域確保
		NeedleWall * pNeedleWall = new NeedleWall;

		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		D3DXVECTOR3 wPosition;
		int wKind;

		//種類
		wKind = (int)LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, wsNum, "kind");

		//位置
		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, wsNum, "posZ");

		//初期化
		pNeedleWall->Initialize(wKind, wPosition);

		//vectorに追加
		m_vecNeedleWall.push_back(pNeedleWall);
	}
}

//テキストからロードして初期化(スイッチ)
void NeedleWallManage::SwitchTextLoadInitialize()
{
	int wMax = (int)LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, "Switch", "max");

	//ファイル読み込みが終わっていなければ
	for (int i = 0; i < wMax; i++)
	{
		D3DXVECTOR3 wPosition;

		//領域確保
		Switch * pSwitch = new Switch;

		//iを文字列に変換
		std::string wsNum = std::to_string(i);

		//スイッチ
		wPosition.x = LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, "Switch : " + wsNum, "posX");
		wPosition.y = LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, "Switch : " + wsNum, "posY");
		wPosition.z = LoadInitializeText(INITIALIZE_TEXT_NEEDLEWALL, "Switch : " + wsNum, "posZ");

		//初期化
		pSwitch->Initialize(wPosition);

		//vectorに追加
		m_vecSwitch.push_back(pSwitch);
	}
}

//踏んだスイッチの順番セーブ
void NeedleWallManage::PushSwitchSave(Engine * pEngine)
{
	//デバック用
	int wKeyNum[5] = { DIK_NUMPAD0, DIK_NUMPAD1, DIK_NUMPAD2, DIK_NUMPAD3, DIK_NUMPAD4 };

	for (int i = 0; i < (int)m_vecSwitch.size(); i++)
	{
		//デバック用でキー入力受付
		if (pEngine->GetKeyStateSync((BYTE)wKeyNum[i]))
		{
			if (!m_vecSwitch[i]->GetPush())
			{
				m_vecSwitch[i]->ChangeFlagPush(true);

				//押したスイッチの番号を追加
				m_vecPushSwitch.push_back(i);

				//チェック開始
				m_bCheck = true;
			}
		}
	}
}


//ギミックのパスワードと入力をチェックする
void NeedleWallManage::CheckGimmickPassward()
{
	//押されたスイッチの番号と正解の番号を比べる
	if (m_vecPushSwitch[m_checkIndex] == m_vecGimmick[m_checkIndex])
	{
		//================================//
		//          一致の場合		      //
		//================================//

		if (!m_bTimeSet)
		{
			//タイムセット
			m_imCheck.SetInterval(1500);
			m_bTimeSet = true;
		}

		//時間が経過したら
		if (m_imCheck.GetTiming())
		{
			//チェック終了
			m_bCheck = false;

			//フラグを戻す
			m_bTimeSet = false;

			//カウントや増やす
			m_checkIndex++;
		}

		//スイッチの数と同じか？
		if (m_checkIndex == (int)m_vecSwitch.size())
		{
			//クリア！！
			m_bClear = true;

			//チェックリセット
			CheckReset();
		}
	}
	else
	{
		//================================//
		//          不一致の場合		  //
		//================================//

		//移動用の番号がスイッチの数と同じになったら
		if (m_moveIndex == (int)m_vecNeedleWall.size())
		{
			//ゲームオーバー
			m_bGameOver = true;

			//リセット
			m_moveIndex = 0;
		}

		//ゲームオーバーでなければ
		if (!m_bGameOver)
		{
			//正解の場所の針を動かす
			if (!m_vecNeedleWall[m_vecGimmick[m_moveIndex]]->GetMove())
			{
				m_vecNeedleWall[m_vecGimmick[m_moveIndex]]->ChangeFlagMove(true);
			}

			//針壁が動き終わったか
			if (m_vecNeedleWall[m_vecGimmick[m_moveIndex]]->GetMoved())
			{
				//チェックリセット
				CheckReset();

				//チェック終了
				m_bCheck = false;

				//カウントを増やす
				m_moveIndex++;
			}
		}
	}
}

//スイッチをもとに戻す
void NeedleWallManage::SwitchRevert()
{
	for (int i = 0; i < (int)m_vecSwitch.size(); i++)
	{
		m_vecSwitch[i]->ChangeFlagPush(false);
		m_vecSwitch[i]->ChangeFlagReturn(true);
	}
}

//チェックリセット
void NeedleWallManage::CheckReset()
{
	//スイッチをもとに戻す
	SwitchRevert();

	//vector削除
	m_vecPushSwitch.clear();

	//チェック用リセット
	m_checkIndex = 0;
}

//最後の動き
void NeedleWallManage::FinalMove()
{
	for (NeedleWall * pNeedleWall : m_vecNeedleWall)
	{
		if (!pNeedleWall->GetFinalMove())
		{
			//すべて動かす
			pNeedleWall->ChangeFlagFinalMove(true);
		}
	}
}

//針の壁を戻す
void NeedleWallManage::Return()
{
	for (NeedleWall * pNeedleWall : m_vecNeedleWall)
	{
		//針の壁が移動していたら
		if (pNeedleWall->GetMoved())
		{
			//針の壁を戻す
			pNeedleWall->ChangeFlagReturn(true);
		}
	}
}