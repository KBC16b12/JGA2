#pragma once
class ResultScene : public IGameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	ResultScene();
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~ResultScene();
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

	void PostRender(CRenderContext& renderContext, int cameraNum) override;

	void SetPosition(CVector3 Spos)
	{
		Spos = Spos;
	}

	void SetData(int killCount)
	{
		m_killcount = killCount;
	}

	void SetPlayerNum(int playerNum)
	{
		m_playerNum = playerNum;
	}

	void SetPlayerKillScore(int *killscore)
	{
		for (int i = 0;i < 4;i++)
		{
			pKill[i] = killscore[i];
		}
	}



private:

	void Draw(CRenderContext& renderContext);

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//BGM�\�[�X�B

	CTexture*					m_SampleTex;						//!<�T���v���̃e�N�X�`���B
	CSprite						m_Sample;							//!<�T���v���̃X�v���C�g�B

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;

	CVector3					Spos;
	int							m_rcount;
	int							m_killcount;		//�L����
	int							m_playerNum;
	int							pNum[4];
	int                         pKill[4];
	int							tmp = 0;
	CTexture*					m_texture[4];
	CTexture*					m_numTexture[10];
	CSprite						m_killScore[4][2];
	CSprite						m_sprite[4];
	CSprite						m_sprite2[4];
	int							m_state;
	float						m_positionLimit;
	float						m_intervalTime;

};

