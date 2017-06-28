#pragma once

class Player;
class TimeSprite;
#include "../../Map/Map.h"
#include "PlayerMeshCommon.h"

#define END_TIMER 1.0f

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

	Player* const GetPlayer(int playernum)
	{
		return m_map->GetPlayer(playernum);
	}

	void SetActiveFlags(bool flag);

	Player* g_player;

	bool IsTimeOver()
	{
		return (0.0f < m_end_timer);
	}

	/*!
	*@brief	�x���`��֐��B
	@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*@param[in]		renderContext		�����_�����O�R���e�L�X�g�B
	*/
	void PostRender(CRenderContext& renderContext) override;

	void PostRender(CRenderContext& renderContext, int cameraNum) override;

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	bool						m_isLoad;
	char*						m_bgm_path;						//BGM�̃t�@�C���p�X
	CSoundSource*				m_bgm;							//BGM�\�[�X�B
	Player*						m_player[PLAYER_NUM];			//�v���C��
	Map*						m_map;							//�}�b�v
	CCamera						m_camera;						//!<�J�����B
	CLight						m_light;						//!<���C�g�B
	RunStat						m_runstat = enFadeIn;			//�t�F�[�h�X�e�[�^�X
	SceneData					m_scenedata;					//��ʑJ�ڃf�[�^
	TimeSprite*					m_time;
	CAnimation					m_playerAnimation;

	float						m_end_timer;

	CTexture*					m_TimerOverTex;						//!<�T���v���̃e�N�X�`���B
	CSprite						m_TimerOver;						//!<�T���v���̃X�v���C�g�B
};

extern GameScene* g_gameScene;
//PincerBullet�p�̃��f��
extern CSkinModelData* g_bulletModel;

extern const PlayerMeshState g_playerMeshState[PLAYERMESHNUM];
extern std::vector<CSkinModelData*> g_playerMeshModel;
