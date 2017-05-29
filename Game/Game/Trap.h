#pragma once
#include "../Game/Map/MapChip.h"

class Player;

class TrapA : public MapChip
{
public:
	TrapA();
	~TrapA();
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
	bool						m_stup;
	bool						m_activeFlg;			//����ł邩�����Ă邩
	CMeshCollider				m_meshCollider;			//���b�V���R���C�_�[�B
	CRigidBody					m_rigidBody;			//���́B
	bool						Flg;
	float						l_playerRadiusF = 3.0f;
};