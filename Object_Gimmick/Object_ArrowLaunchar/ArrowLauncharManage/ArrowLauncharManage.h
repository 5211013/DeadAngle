//*****************************************************************************
//
// 矢の発射ギミック
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

#include "..\\Arrow\\Arrow.h"
#include "..\\Launchar\\Launchar.h"
#include "..\\..\\Object_Switch\\Switch\\Switch.h"

#include <fstream>

class ArrowLauncharManage : public BaseObject
{
public:

	ArrowLauncharManage();

	~ArrowLauncharManage();

	//初期化
	void Initialize(Engine * pEngine, Common::CommonData & gameData);

	//更新
	void Update(Engine * pEngine);

	//描画
	void Draw(Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);

	//デバック用
	void Debug(Engine * pEngine);
	
private:

	//スイッチのパーツ
	enum 
	{
		FLOOR,
		SWITCH,
		MAX_PARTS,
	};

	//ギミック番号
	int m_gimmickNo;

	//ギミック番号チェック用
	int m_checkGimmickNo;

	//発射口
	NormalMap m_launchar;

	//矢
	NormalMap m_arrow;

	//スイッチ
	NormalMap m_switch[MAX_PARTS];

	//ファイル読み込み用
	std::ifstream m_ifsArrowLauncharManage;

	//発射口用コンテナ(vector)
	std::vector<Launchar*> m_vecLaunchar;

	//矢用コンテナ(vector)
	std::vector<Arrow*> m_vecArrow;

	//スイッチ用コンテナ(vector)
	std::vector<Switch*> m_vecSwitch;

	//発射口データを読み込む
	void ArrowLauncharDataLoad();

	//発射口データを読み込む
	void ArrowDataLoad(const D3DXVECTOR3 launcharDir, const D3DXMATRIX matWorld);

	//発射口データを読み込む
	void SwitchDataLoad();

	//テキストからロードして初期化(矢と発射口)
	void TextLoadInitialize();

	//テキストからロードして初期化(スイッチ)
	void SwitchTextLoadInitialize();

	//コピーガード
	ArrowLauncharManage& operator=(const ArrowLauncharManage&);
	ArrowLauncharManage(const ArrowLauncharManage&);
};