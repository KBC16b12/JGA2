#pragma once

#include "MapChip.h"

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
	
	/*!
	*@brief	�x���`��֐��B
	@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*@param[in]		renderContext		�����_�����O�R���e�L�X�g�B
	*/
	void Render(CRenderContext& renderContext, int playernum) override;

	void PostRender(CRenderContext& renderContext, int playernum) override;

	bool IsLoadEnd()
	{
		return m_isLoad;
	}

	const std::vector<MapChip*>& GetMap()
	{
		return m_mapchip;
	}

private:
	bool						m_isLoad;
	std::vector<MapChip*>		m_mapchip;			//�}�b�v�`�b�v���X�g
};

