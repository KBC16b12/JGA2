#pragma once
//�A�C�e���̔z�u���
struct ItemPosData
{
	SMapInfo	m_mapDat;
	bool		m_isUse;	//�Q�[�����X�^�[�g����Ƃ��Ɍ��߂�z�u�����t���O�𗧂ĂĂ��Ԃ�Ȃ��悤�ɂ���
};

//�v���C���[�̔z�u���
struct PlayerPosData
{
	SMapInfo	m_mapDat;
	bool		m_isUse;	//�Q�[�����X�^�[�g����Ƃ��Ɍ��߂�z�u�����t���O�𗧂ĂĂ��Ԃ�Ȃ��悤�ɂ���
};

class RandomPosManager
{
public:
	RandomPosManager();

	~RandomPosManager();


	//�v���C���[�̃f�[�^��ǉ�
	void AddPlayerData(SMapInfo mapDat)
	{
		m_playerData.push_back({ mapDat, false });
	}

	//�A�C�e���̃f�[�^��ǉ�
	void AddItemData(SMapInfo mapDat)
	{
		m_itemData.push_back({mapDat, false});
	}

	//���X�|�[�����̃v���C���[�̔z�u�����擾
	SMapInfo GetPlayerRespawnPos(int playerNum);

	//�X�^�[�g���̃v���C���[�̔z�u�����擾(�z�u��񎩑̂̓��X�|�[�����̂��̂ƈꏏ
	SMapInfo GetPlayerStartPos();

	//�A�C�e���̔z�u�����擾
	SMapInfo GetItemData();

private:
	std::vector<PlayerPosData> m_playerData;
	std::vector<ItemPosData> m_itemData;
};

extern RandomPosManager *g_randomPosManager;