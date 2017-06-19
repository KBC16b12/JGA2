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

	virtual ~Item();
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

	virtual void PostRender(CRenderContext& renderContext, int playernum)override;

	virtual void PostRender(CRenderContext& renderContext)override;

	bool IsDeath()
	{
		return m_isDeath;
	}
protected:

	virtual void Death(Player *player);

	void SetSpritePosition();

protected:
	const CVector2				m_size = {500.0f, 500.0f};
	CVector2					m_screenPos[PLAYER_NUM];
	CVector2					m_spriteSize[PLAYER_NUM];
	CTexture*					m_texture;
	CSprite						m_sprite;
	//CMeshCollider				m_meshCollider;		//���b�V���R���C�_�[�B
	//CRigidBody					m_rigidBody;		//���́B
	CSkinModel					m_SkinModel;		//�X�L�����f��
	CVector3					m_position;			//���W
	CQuaternion					m_rotation;			//��]
	bool						m_isDeath;
	bool						m_isSpriteRender;

};
