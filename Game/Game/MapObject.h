#pragma once
#include "C:\Users\kbc16\Documents\github\JGA2\Game\Game\Map\MapChip.h"
class MapObject : public MapChip
{
public:
	MapObject();


	~MapObject();


	/*!
	*@brief �������֐�
	*/
	void Init(SMapInfo map_dat) override;

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


	/*!
	*@brief	�`��֐��B
	*@param[in]		renderContext		�����_�����O�R���e�L�X�g�B
	*@param[in]		playernum			�ǂ̃v���C���[�ɕ`�悵������
	*/
	void Render(CRenderContext& renderContext, int cameranum) override;

private:
	CMeshCollider				m_meshCollider;		//���b�V���R���C�_�[�B
	CRigidBody					m_rigidBody;		//���́B

};

