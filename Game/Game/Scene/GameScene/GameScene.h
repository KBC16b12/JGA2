#pragma once

class Player;
class Map;

/*!
 *@brief	�Q�[���V�[���B
 */
class GameScene : public IGameObject
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	GameScene();

	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~GameScene();

	/*!
	*@brief �������֐�
	*/
	void Init(std::vector<SMapInfo> map_data);

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
	*/
	void Render(CRenderContext& renderContext);

	/*!
	*@brief	�x���`��֐��B
	@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*@param[in]		renderContext		�����_�����O�R���e�L�X�g�B
	*/
	void PostRender(CRenderContext& renderContext) override;

	void SetActiveFlags(bool flag);

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//BGM�\�[�X�B
	Player*						m_player;						//�v���C��
	Map*						m_map;							//�}�b�v

	CTexture*					m_texture[10];
	CSprite						m_timesprite[3];
	CSprite						m_killsprite[2];

	CCamera						m_camera;								//!<�J�����B

	CLight						m_light;								//!<���C�g�B

	RunStat						m_runstat = enFadeIn;			//�t�F�[�h�X�e�[�^�X

	SceneData					m_scenedata;					//��ʑJ�ڃf�[�^

	int m_time;				//�^�C�}�[
	int m_killcount;		//�L����
};

extern GameScene* g_gameScene;
