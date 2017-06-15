#include "stdafx.h"
#include "RandomPosManager.h"
#include "Scene/GameScene/GameScene.h"
#include "Player/Player.h"

extern RandomPosManager *g_randomPosManager = nullptr;

RandomPosManager::RandomPosManager()
{

}

RandomPosManager::~RandomPosManager()
{

}


SMapInfo RandomPosManager::GetPlayerRespawnPos(int playerNum)
{
	int l_vectorNum;
	bool l_isLoop;
	Player* l_player[PLAYER_NUM];
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		l_player[i] = g_gameScene->GetPlayer(i);
	}
	do
	{
		l_isLoop = false;
		l_vectorNum = (int)(g_random.GetRandInt() % m_playerData.size());
		CVector3 l_position = m_playerData[l_vectorNum].m_mapDat.s_position;
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			if (i == playerNum)
			{
				continue;
			}
			CVector3 distance = l_player[i]->GetPosition();
			distance.Subtract(l_position);
			if (distance.Length() < 20.0f)
			{
				l_isLoop = true;
				break;
			}
		}

	} while (l_isLoop);

	return m_playerData[l_vectorNum].m_mapDat;
}

SMapInfo RandomPosManager::GetPlayerStartPos()
{
	int l_vectorNum;
	do
	{
		l_vectorNum = (int)(g_random.GetRandInt() % m_playerData.size());
	} 
	while (m_playerData[l_vectorNum].m_isUse);
	m_playerData[l_vectorNum].m_isUse = true;
	return m_playerData[l_vectorNum].m_mapDat;
}

SMapInfo RandomPosManager::GetItemData()
{
	int vectorNum;
	do
	{
		vectorNum = (int)(g_random.GetRandInt() % m_itemData.size());
	}
	while (m_itemData[vectorNum].m_isUse);
	m_itemData[vectorNum].m_isUse = true;
	return m_itemData[vectorNum].m_mapDat;

}