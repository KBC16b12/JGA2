#pragma once
#include "C:\Users\kbc16\Documents\github\JGA2\Game\Game\Map\MapChip.h"

/*
�}�b�v�ɂ���A�C�e���{�b�N�X�̃N���X
*/

class Player;

class Item : public MapChip
{
public:
	Item();

	~Item();
	/*
	*@brief �������֐�
	*/
	void Init(SMapInfo map_dat)override;

	/*
	*@brief �X�V�֐�
	*/
	void Update()override;

	/*
	*@brief �`��֐�
	*@brief playernum �ǂ̃v���C���[�̎��_�ŕ`�悵������
	*/
	void Render(CRenderContext& renderContext, int playernum)override;

private:
	RigidBodyInfo				m_rbInfo;				//���̂̃X�e�[�^�X
	bool						m_activeFlg;			//����ł邩�����Ă邩
	CMeshCollider				m_meshCollider;			//���b�V���R���C�_�[�B
	CRigidBody					m_rigidBody;			//���́B
	Player*						m_player[PLAYER_NUM];	//�v���C���[�̃C���X�^���X
	int							m_intervalTime;			//�󂳂�Ă��玟�o������܂ł̎��Ԃ��J�E���g����ϐ�
	bool						m_rigidBodyFlg;
};
