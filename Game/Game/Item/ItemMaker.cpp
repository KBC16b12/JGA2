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
	SkinModelDataResources().Load(m_modelDataItemBox,"Assets/modelData/ItemBox.X", NULL, false, 1);
	SkinModelDataResources().Load(m_modelDataMimic, "Assets/modelData/ItemBox.X", NULL, false, 1);
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
		if (15.0f < m_intervalTime)
		{
			//if (g_random.GetRandInt() % 3 != 0)
			//{
				m_item = NewGO<ItemBox>(PRIORITY1);
			//}
			//else
			//{
			//	m_item = NewGO<Mimikku>(PRIORITY1);
			//}
			m_item->Init(m_position, m_rotation, m_modelDataItemBox.GetBody());
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