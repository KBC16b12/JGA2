#pragma once
class PincerAttackEffect;

class PincerAttack :
	public IGameObject
{
public:
	PincerAttack();

	~PincerAttack();

	void Init(int playerNum)
	{
		m_playerNum = playerNum;
	}

	bool Start();

	void Update()override;

	void CreatePrimitiv();

	void Render(CRenderContext& renderContext)override;

	void Render(CRenderContext& renderContext, int playerNum)override;

	void Shoot();
private:
	PincerAttackEffect*	m_pincerEffect[PLAYER_NUM - 1];
	int					m_playerNum;
};

