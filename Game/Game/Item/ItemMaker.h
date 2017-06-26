#pragma once
#include "Item.h"
#include "Map/MapChip.h"

class ItemMaker : public MapChip
{
public:
	ItemMaker();

	~ItemMaker();

	/*
	*@brief �X�V�֐�
	*/
	void Update()override;

	/*
	*@brief �`��֐�
	*@brief playernum �ǂ̃v���C���[�̎��_�ŕ`�悵������
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
	CAnimation				m_itemBoxAnime;
	CAnimation				m_mimicAnime;

};