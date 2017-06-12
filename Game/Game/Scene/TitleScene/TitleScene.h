#pragma once

/*!
 *@brief	�^�C�g���V�[���B
 */
class TitleScene : public IGameObject
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	TitleScene();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~TitleScene();

	/*!
	*@brief �������֐�
	*/
	void Init(RunStat stat);

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

	void Render(CRenderContext& renderContext) override;

	void Render(CRenderContext& renderContext, int cameraNum)override;

	void PostRender( CRenderContext& renderContext ) override;

	void PostRender(CRenderContext& renderContext, int cameraNum) override;
private:

	void Draw(CRenderContext& renderContext);
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//BGM�\�[�X�B

	CTexture*					m_TitleTex;							//!<�w�i�̃e�N�X�`���B
	CSprite						m_Title;							//!<�w�i�̃X�v���C�g�B

	CTexture*					m_StartTex;							//!<�w�i�̃e�N�X�`���B
	CSprite						m_Start;							//!<�w�i�̃X�v���C�g�B

	CEffect*					m_pEffect;
	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;
	float						m_alpha;
	bool						m_isAlpha;
};

