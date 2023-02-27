//*****************************************************************************
//
// ゲームシーンの石の台に置く石の管理
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

#include "..\\Stone\\Stone.h"
#include "..\\StoneSet\\StoneSet.h"

#include <fstream>

class StoneManage : public BaseObject
{
public:

	StoneManage();
	
	//初期化
	void Initialize(Engine * pEngine, Common::CommonData & gameData);

	//更新
	void Update(Engine * pEngine, const D3DXVECTOR3 playerPos);

	//描画
	void Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//デバック用
	void Debug(Engine * pEngine);

private:

	//石
	enum 
	{
		RIGHT_STAGE,
		LEFT_STAGE,
		MAX_STONE,
	};

	//石の台
	enum
	{
		STONE_SET_RIGHT_STAGE,
		STONE_SET_LEFT_STAGE,
		STONE_SET_RIGHT_CENTER,
		STONE_SET_LEFT_CENTER,
		MAX_STONESET,
	};

	//モデルの種類
	enum 
	{
		STONE,
		STONE_SET,
		MAX_MODEL,
	};

	//石の置き場の調節用
	const D3DXVECTOR3 STONE_SET_ADJUST;

	//モデル
	NormalMap m_model[MAX_MODEL];

	//石
	Stone m_stone[MAX_STONE];

	//石の台
	StoneSet m_stoneSet[MAX_STONESET];

	//テキストからデータロード
	void TextDataLoad();

	//テキストからデータロード(石の台)
	void StoneSetTextDataLoad();
};