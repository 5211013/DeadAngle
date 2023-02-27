//*****************************************************************************
//
// 鉄格子の管理
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\BaseObject\\BaseObject.h"

#include "..\\IronBars\\IronBars.h"
#include "..\\IronBarsBottom\\IronBarsBottom.h"
#include <fstream>

class IronBarsManage : BaseObject
{
public:

	IronBarsManage();

	//初期化
	void Initialize(Engine * pEngine, Common::CommonData & gameData);

	//更新
	void Update(Engine * pEngine, const D3DXVECTOR3 playerPos, const bool bNeedleWallClear);

	//描画
	void Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);
	
	//デバッグ用
	void Debug(Engine * pEngine);

private:

	//モデルの種類
	enum 
	{
		IRONBARS, //本体
		BOTTOM,   //下の部分
		MAX_KIND,
	};

	//場所
	enum 
	{
		ENTRANCE, //入口
		EXIT,     //出口
		MAX_NUM,
	};

	//さがる範囲
	const float DOWN_RANGE;

	//鉄格子
	IronBars m_ironBars[MAX_NUM];

	//鉄格子の枠
	IronBarsBottom m_ironBarsBottom[MAX_NUM];

	//モデル
	NormalMap m_model[MAX_KIND];

	//テキストからロードして初期化
	void TextLoadInitialize();

	//プレイヤーとの距離
	bool DownRange(const D3DXVECTOR3 playerPos);
};