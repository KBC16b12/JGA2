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
	float					m_recoveryTime;				//ダメージを食らってから回復し始めるまでの時間
	float					m_lifeRecoveryInterval;		//回復し始めてから徐々に回復していくための時間
	bool					m_isBulletHit;				//弾が当たった時のフラグ
	int*					m_hp;						//プレイヤーのHP
	int						m_maxHp;					//プレイヤーのMAXHP
};
