//*****************************************************************************
//
// ゲームシーンの石の台に置く石
//
//*****************************************************************************

#pragma once

#include "..\\..\\..\\..\\..\\GameBase.h"
#include "..\\..\\..\\..\\BaseObject\\BaseObject.h"

class Stone : public BaseObject
{
public:

	Stone();

	//初期化
	void Initialize(const D3DXVECTOR3 position);

	//更新
	void Update();

	//描画
	void Draw(NormalMap * pNormalMap, Camera * pCamera, Projection * pProjection, AmbientLight * pAmbient, DirectionalLight * pLight);
	
	//入手フラグ取得
	bool GetHave();

	//位置をセット
	void SetPosition(const D3DXVECTOR3 position);

	//入手フラグ切替
	void ChangeFlagGet(const bool bWhich);

private:

	//入手用
	bool m_bHave;
};