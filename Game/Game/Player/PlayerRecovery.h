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
	float					m_recoveryTime;				//ダメージを食らってから回復し始めるまでの時間
	float					m_lifeRecoveryInterval;		//回復し始めてから徐々に回復していくための時間
	int						m_playerNum;
	bool					m_isBulletHit;				//弾が当たった時のフラグ
	int*					m_hp;						//プレイヤーのHP
	int						m_maxHp;					//プレイヤーのMAXHP
	CSprite					m_sprite;
	CTexture*				m_texture;
};
