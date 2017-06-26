#pragma once
class PlayerRecovery : public IGameObject
{
public:
	PlayerRecovery();
	~PlayerRecovery();

	void Init(int *hp, int maxHp, int playerNum)
	{
		m_hp = hp;
		m_maxHp = maxHp;
		m_playerNum = playerNum;
	}

	bool Start()override;

	void Recovery();

	void Update()override;

	void Hit();

	void PostRender(CRenderContext& renderContext, int playerNum)override;

	void PostRender(CRenderContext& renderContext)override;

private:
	float					m_recoveryTime;				//�_���[�W��H����Ă���񕜂��n�߂�܂ł̎���
	float					m_lifeRecoveryInterval;		//�񕜂��n�߂Ă��珙�X�ɉ񕜂��Ă������߂̎���
	int						m_playerNum;
	bool					m_isBulletHit;				//�e�������������̃t���O
	int*					m_hp;						//�v���C���[��HP
	int						m_maxHp;					//�v���C���[��MAXHP
	CSprite					m_sprite;
	CTexture*				m_texture;
};
