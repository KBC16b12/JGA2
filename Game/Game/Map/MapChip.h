#pragma once

struct Status::SMapInfo;

/*
*@brief �}�b�v�`�b�v�Ƃ��ă}�b�v�ɔz�u����I�u�W�F�N�g�̐e�N���X
*/

class MapChip : public IGameObject
{
public:	
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	MapChip();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~MapChip();

	/*!
	*@brief �������֐�
	*/
	virtual void Init(SMapInfo map_dat);

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
	*/

	void Render(CRenderContext& renderContext, int cameranum) override;

	bool IsLoadEnd()
	{
		return m_SkinModelData.IsLoadEnd();
	}

protected:
	CSkinModel					m_SkinModel;		//�X�L�����f��
	CSkinModelDataHandle		m_SkinModelData;	//�X�L�����f���̃n���h��
	CVector3					m_position;			//���W
	CQuaternion					m_rotation;			//��]
	CVector3					m_scale;			//�g��
};

