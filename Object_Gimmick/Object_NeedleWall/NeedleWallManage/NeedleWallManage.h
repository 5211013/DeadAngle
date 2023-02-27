//*****************************************************************************
//
// 針の壁のギミックの管理
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

#include "..\\NeedleWall\\NeedleWall.h"
#include "..\\..\\Object_Switch\\Switch\\Switch.h"

#include <fstream>

class NeedleWallManage : public BaseObject
{
public:

	NeedleWallManage();

	~NeedleWallManage();

	//初期化
	void Initialize(Engine * pEngine, Common::CommonData & gameData);

	//更新
	void Update(Engine * pEngine);

	//描画
	void Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//クリアフラグ取得
	bool GetClear() const;

	//デバック用
	void Debug(Engine * pEngine);
	
private:

	//針の壁の種類
	enum 
	{
		CENTER,
		SIDE,
		MAX_KIND,
	};

	//スイッチのパーツ
	enum 
	{
		FLOOR,
		SWITCH,
		MAX_SWITCH_PARTS,
	};

	//針壁移動する用の添え字
	int m_moveIndex;

	//チェック用
	int m_checkIndex;

	//チェック用フラグ
	bool m_bCheck;

	//クリア
	bool m_bClear;

	//ゲームオーバー
	bool m_bGameOver;

	//タイムセット用
	bool m_bTimeSet;

	//最チェックまでの時間
	IntervalManage m_imCheck;

	//モデル
	NormalMap m_needleWall[MAX_KIND];
	NormalMap m_switch[MAX_SWITCH_PARTS];

	//ファイル読み込み用
	std::ifstream m_ifsNeedleWallManage;

	//針の壁用コンテナ(vector)
	std::vector<NeedleWall*> m_vecNeedleWall;

	//スイッチ用コンテナ(vector)
	std::vector<Switch*> m_vecSwitch;

	//ギミック用
	std::vector<int> m_vecGimmick;

	//押されたスイッチ記録用
	std::vector<int> m_vecPushSwitch;

	//テキストからロードして初期化(針の壁)
	void TextLoadInitialize();

	//テキストからロードして初期化(スイッチ)
	void SwitchTextLoadInitialize();

	//踏んだスイッチの順番セーブ
	void PushSwitchSave(Engine * pEngine);

	//ギミックのパスワードと入力をチェックする
	void CheckGimmickPassward();

	//スイッチをもとに戻す
	void SwitchRevert();

	//チェックリセット
	void CheckReset();

	//最後の動き
	void FinalMove();

	//針の壁を戻す
	void Return();

	//コピーガード
	NeedleWallManage& operator=(const NeedleWallManage&);
	NeedleWallManage(const NeedleWallManage&);
};