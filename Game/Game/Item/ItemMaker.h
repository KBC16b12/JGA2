#pragma once
#include "Item.h"
#include "Map/MapChip.h"

class ItemMaker : public MapChip
{
public:
	ItemMaker();

	~ItemMaker();

	/*
	*@brief 更新関数
	*/
	void Update()override;

	/*
	*@brief 描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	void Render(CRenderContext& renderContext, int playernum)override;

	void Render(CRenderContext& renderContext)override;

private:

	void ModelInit(const char* modelName)override;

private:
	Item*	m_item;
	float	m_intervalTime;
	CSkinModelDataHandle	m_modelDataItemBox;
	CSkinModelDataHandle	m_modelDataMimic;

};