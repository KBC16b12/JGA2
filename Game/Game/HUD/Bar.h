#pragma once

class Bar : public IGameObject
{
public:
	/*!
	*@brief	�ǂ���Ɍ����Ă������B
	*/
	enum enBarQuarter
	{
		enQuaUp,
		enQuaDown,
		enQuaLeft,
		enQuaRight,
		enQuaNum,
	};

	enum EnState {
		enState_Normal,
		enState_DamageWait,		//�_���[�W���o�J�n�̑҂��B
		enState_Damage,			//�_���[�W���o�B
	};

	/*!
	*@brief ����ŕ␳��������B
	*/
	struct Correction
	{
		CVector2 pos;
		CVector2 pivot;
	};

	/*!
	*@brief	�R���X�g���N�^�B
	*/
	Bar();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~Bar();

	/*!
	*@brief	�X�V�֐��B
	*/
	void Update();

	/*!
	*@brief	�`��֐��B
	*/
	void PostRender(CRenderContext& renderContext, int playernum);

	void PostRender(CRenderContext& renderContext);

	/*!
	*@brief	�ǂ̌����Ɍ��邩��ݒ�B
	*/
	void SetBerQuarter(enBarQuarter qua)
	{
		m_Quarter = qua;
	}

	/*!
	*@brief	�o�[�̃t�@�C���p�X�ݒ�B
	*/
	void SetBarPath(char* path, unsigned int color = 0)
	{
		if (strcmp(m_BarPath, path) != 0)
		{
			m_BarPath = path;
			m_BarTex = TextureResources().LoadEx(m_BarPath, color);
			m_Bar.SetTexture(m_BarTex);
		}
	}

	/*!
	*@brief	�_���[�W�o�[�̃t�@�C���p�X�ݒ�B
	*/
	void SetBarBackPath(char* path, unsigned int color = 0)
	{
		if (strcmp(m_BarBackPath, path) != 0)
		{
			m_BarBackPath = path;
			m_BarBackTex = TextureResources().LoadEx(m_BarBackPath, color);
			m_BarBack.SetTexture(m_BarBackTex);
		}
	}

	/*!
	*@brief	�w�i�̃t�@�C���p�X�ݒ�B
	*/
	void SetGaugePath(char* path, unsigned int color = 0)
	{
		if (strcmp(m_GaugePath, path) != 0)
		{
			m_GaugePath = path;
			m_GaugeTex = TextureResources().LoadEx(m_GaugePath, color);
			m_Gauge.SetTexture(m_GaugeTex);
		}
	}

	/*!
	*@brief	�o�[�̃f�[�^�ݒ�(�������̏����ōX�V)�B
	*/
	void SetData(int data, int max_data)
	{
		m_data = data;
		m_max_data = max_data;
	}

	/*!
	*@brief	�o�[�̍��W�ݒ�B
	*		���̍��W�̓s�{�b�g�Ɉˑ������A�u�������v�̍��W�ɂ��Ă��������B
	*/
	void SetBarPos(CVector2 pos)
	{
		m_BarPos = pos;
		m_Bar.SetPosition(pos);
		m_BarBack.SetPosition(pos);
	}

	/*!
	*@brief	�o�[�̍ő�T�C�Y�ݒ�B
	*/
	void SetBarMaxSize(CVector2 size)
	{
		m_BarMaxSize = size;
		m_Bar.SetSize(size);
		m_BarBack.SetSize(size);
	}

	/*!
	*@brief	�w�i�̍��W�ݒ�B
	*/
	void SetGaugePos(CVector2 pos)
	{
		m_Gauge.SetPosition(pos);
	}

	/*!
	*@brief	�w�i�̍ő�T�C�Y�ݒ�B
	*/
	void SetGaugeMaxSize(CVector2 size)
	{
		m_Gauge.SetSize(size);
	}

private:
	/*!
	*@brief	�o�[�̍X�V�֐��B
	*/
	void Bar_Update();

	/*!
	*@brief �s�{�b�g��ݒ�B
	*/
	void Bar_Pivot();

	/*!
	*@brief ���W��ݒ�B
	*/
	void Bar_Pos();

	/*!
	*@brief	m_state��enState_Damage�̂Ƃ��ɌĂԁB
	*/
	void Bar_Damage();

	/*!
	*@brief	m_state��enState_Normal�̂Ƃ��ɌĂԁB
	*/
	void Bar_Normal();

	/*!
	*@brief	m_state��enState_DamageWait�̂Ƃ��ɌĂԁB
	*/
	void Bar_Wait();

	CSprite				m_Bar;			//�o�[�B
	CTexture*			m_BarTex;		//�o�[�̃e�N�X�`���B
	char*				m_BarPath;		//�o�[�̃t�@�C���p�X�B
	CVector2			m_BarPos;		//�o�[�̍��W
	
	CVector2			m_BarMaxSize;	//�o�[�̍ő���W
		
	CSprite				m_Gauge;		//�Q�[�W�B
	CTexture*			m_GaugeTex;		//�Q�[�W�̃e�N�X�`���B
	char*				m_GaugePath;	//�Q�[�W�̃t�@�C���p�X�B

	CSprite				m_BarBack;		//�o�[�̔w�i�B
	CTexture*			m_BarBackTex;	//�o�[�̔w�i�̃e�N�X�`��
	char*				m_BarBackPath;	//�o�[�̔w�i�̃t�@�C���p�X

	int					m_data;			//���݂̒l
	int					m_old_data;		//���O�̒l
	int					m_max_data;		//�ő�l

	float				m_timer;		//�^�C�}�[�B

	EnState				m_state;		//�_���[�W���o�X�e�[�^�X

	enBarQuarter		m_Quarter;		//�ǂ���Ɍ����Ă�����
};


