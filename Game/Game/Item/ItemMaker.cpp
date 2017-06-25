#include "stdafx.h"
#include "ItemMaker.h"
#include "ItemBox.h"
#include "../Mimikku.h"

ItemMaker::ItemMaker()
{
	m_item = nullptr;
	m_intervalTime = 30.0f;
}

ItemMaker::~ItemMaker()
{
	if (m_item != nullptr)
	{
		DeleteGO(m_item);
	}
}

void ItemMaker::ModelInit(const char* modelName)
{
	SkinModelDataResources().Load(m_modelDataItemBox,"Assets/modelData/ItemBox.X", &m_itemBoxAnime, false, 1);
	SkinModelDataResources().Load(m_modelDataMimic, "Assets/modelData/Mimic.X", &m_mimicAnime, false, 1);
	m_mimicAnime.PlayAnimation(0);
	m_itemBoxAnime.PlayAnimation(0);
}

void ItemMaker::Update()
{
	if (m_item != nullptr)
	{
		if (m_item->IsDeath())
		{
			DeleteGO(m_item);
			m_item = nullptr;
		}
	}
	else
	{
		m_intervalTime += GameTime().GetFrameDeltaTime();
		if (/*15.0f*/1.0f < m_intervalTime)
		{
			CSkinModelData *l_skinModelData = nullptr;
			CAnimation*		l_animation = nullptr;
			if (g_random.GetRandInt() % 2 != 0)
			{
				m_item = NewGO<ItemBox>(PRIORITY1);
				l_skinModelData = m_modelDataItemBox.GetBody();
				l_animation = &m_itemBoxAnime;
			}
			else
			{
				m_item = NewGO<Mimikku>(PRIORITY1);
				l_skinModelData = m_modelDataMimic.GetBody();
				l_animation = &m_mimicAnime;
			}
			m_item->Init(m_position, m_rotation, l_skinModelData, l_animation);
			m_intervalTime = 0.0f;
		}
	}
}

void ItemMaker::Render(CRenderContext& renderContext)
{

}

void ItemMaker::Render(CRenderContext& renderContext, int playerNum)
{

}