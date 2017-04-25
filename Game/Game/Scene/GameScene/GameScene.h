#pragma once

class Player;
class Map;
class TimeSprite;

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
	void Init(std::vector<SMapInfo> map_data, char* bgm_path);

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
	void Render(CRenderContext& renderContext, int playernum)override;

	void PostRender(CRenderContext& renderContext, int playernum)override;

	Player* const GetPlayer(int playernum)
	{
		return m_player[playernum];
	}

	void SetActiveFlags(bool flag);

	void OnDestroy();

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();


	char*						m_bgm_path;						//BGM�̃t�@�C���p�X
	CSoundSource*				m_bgm;							//BGM�\�[�X�B
	Player*						m_player[PLAYER_NUM];						//�v���C��
	Map*						m_map;							//�}�b�v
	CCamera						m_camera;								//!<�J�����B
	CLight						m_light;								//!<���C�g�B
	RunStat						m_runstat = enFadeIn;			//�t�F�[�h�X�e�[�^�X
	SceneData					m_scenedata;					//��ʑJ�ڃf�[�^
	TimeSprite*					m_time;
};

extern GameScene* g_gameScene;
