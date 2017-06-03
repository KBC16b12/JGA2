#pragma once
class PlayerRecovery : public IGameObject
{
public:
	PlayerRecovery();
	~PlayerRecovery();

	void Init(int *hp, int maxHp)
	{
		m_hp = hp;
		m_maxHp = maxHp;
	}

	void Update()override;

	void Hit();
private:
	float					m_recoveryTime;				//�_���[�W��H����Ă���񕜂��n�߂�܂ł̎���
	float					m_lifeRecoveryInterval;		//�񕜂��n�߂Ă��珙�X�ɉ񕜂��Ă������߂̎���
	bool					m_isBulletHit;				//�e�������������̃t���O
	int*					m_hp;						//�v���C���[��HP
	int						m_maxHp;					//�v���C���[��MAXHP
};
