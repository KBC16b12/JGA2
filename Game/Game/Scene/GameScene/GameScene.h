#pragma once

class Player;
class TimeSprite;
#include "../../Map/Map.h"

#define PARTICLE_NUM 20

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
		return m_map->GetPlayer(playernum);
	}

	void SetActiveFlags(bool flag);

	void OnDestroy();

	bool IsLoadEnd()
	{
		return m_isLoad;
	}

	void ParticleEmit(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition);

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	bool						m_isLoad;
	char*						m_bgm_path;						//BGM�̃t�@�C���p�X
	CSoundSource*				m_bgm;							//BGM�\�[�X�B
	Map*						m_map;							//�}�b�v
	CCamera						m_camera;								//!<�J�����B
	CLight						m_light;								//!<���C�g�B
	RunStat						m_runstat = enFadeIn;			//�t�F�[�h�X�e�[�^�X
	SceneData					m_scenedata;					//��ʑJ�ڃf�[�^
	TimeSprite*					m_time;
	CParticleEmitter*			m_particle[PARTICLE_NUM];
};

extern GameScene* g_gameScene;
