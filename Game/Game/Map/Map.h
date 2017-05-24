#pragma once

#include "MapChip.h"
class Player;

class Map : public IGameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	Map();
	
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~Map();
	
	/*!
	*@brief �������֐�
	*@details 
	*/
	void Init(std::vector<SMapInfo> map_dat);

	/*!
	*@brief	�J�n�֐��B
	*@details
	* �������Ȃǂ����̊֐��Ɏ������Ă��������B</br>
	* ���̊֐���true��Ԃ��Ɩ{�ِ��͈ȍ~�̃t���[���ł͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �����ăQ�[���I�u�W�F�N�g�̏�Ԃ������������ɂȂ�Update�֐����Ă΂��悤�ɂȂ�܂��B</br>
	*@return	true���A���Ă����珉���������B
	*/
	bool Start() override;
	
	/*!
	*@brief	�X�V�֐��B
	*/
	void Update() override;

	Player* GetPlayer(int playerNum)
	{
		return m_player[playerNum];
	}

	const std::vector<MapChip*>& GetMap()
	{
		return m_mapchip;
	}

private:
	bool						m_isLoad;
	Player*						m_player[PLAYER_NUM];
	std::vector<MapChip*>		m_mapchip;			//�}�b�v�`�b�v���X�g
};

