#pragma once
#include "Map/MapChip.h"

/*
�}�b�v�ɂ���A�C�e���{�b�N�X�̃N���X
*/

class Player;

class Item : public IGameObject
{
public:
	Item();

	~Item();
	/*
	*@brief �������֐�
	*/
	virtual void Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModelData);

	/*
	*@brief �X�V�֐�
	*/
	virtual void Update()override;

	virtual bool Start()override;

	/*
	*@brief �`��֐�
	*@brief playernum �ǂ̃v���C���[�̎��_�ŕ`�悵������
	*/
	virtual void Render(CRenderContext& renderContext, int playernum)override;

	virtual void Render(CRenderContext& renderContext)override;

	bool IsDeth()
	{
		return m_isDeth;
	}
protected:
	virtual void Deth(Player *player);

private:
	CMeshCollider				m_meshCollider;			//���b�V���R���C�_�[�B
	CRigidBody					m_rigidBody;			//���́B
	CSkinModel					m_SkinModel;		//�X�L�����f��
	CVector3					m_position;			//���W
	CQuaternion					m_rotation;			//��]
	bool						m_isDeth;

};
