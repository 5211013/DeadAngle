//*****************************************************************************
//
// ゲームシーンの岩の振り子の管理
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

#include "..\\RockPendulum\\RockPendulum.h"

#include <fstream>

class RockPendulumManage : public BaseObject
{
public:

	RockPendulumManage();

	~RockPendulumManage();

	//初期化
	void Initialize(Engine * pEngine, Common::CommonData & gameData);

	//更新
	void Update();

	//描画
	void Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);
	
private:

	//モデル
	NormalMap m_rockPendulum;

	//ファイル読み込み用
	std::ifstream m_ifsRockPendulum;

	//岩の振り子用コンテナ(vector)
	std::vector<RockPendulum*> m_vecRockPendulum;

	//テキストからロードして初期化
	void TextLoadInitialize();

	//コピーガード
	RockPendulumManage& operator=(const RockPendulumManage&);
	RockPendulumManage(const RockPendulumManage&);
};