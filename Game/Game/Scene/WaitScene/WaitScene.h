#pragma once
class WaitScene : public IGameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	WaitScene();
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~WaitScene();
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
	void PostRender(CRenderContext& renderContext) override;

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	CTexture*					m_SampleTex;						//!<�T���v���̃e�N�X�`���B
	CSprite						m_Sample;							//!<�T���v���̃X�v���C�g�B

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;
};

