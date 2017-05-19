#pragma once

class PincerAttackEffect :
	public IGameObject
{
public:
	PincerAttackEffect();
	~PincerAttackEffect();

	void Init(int playerNum, int opponentNum)
	{
		m_playerNum = playerNum;
		m_opponentNum = opponentNum;
	}

	bool Start()override;

	void Update()override;

	void Render(CRenderContext& renderContext)override;

	void Render(CRenderContext& renderContext, int playerNum)override;
	
private:
	void Draw(CRenderContext& renderContext, CMatrix l_wvp);

private:
	int					m_playerNum;
	int					m_opponentNum;
	CPrimitive			m_primitive;
	CLight				m_light;
	CEffect*			m_pEffect;
	CMatrix				m_worldMatrix;
	CMatrix				m_rotationMatrix;
	CMatrix				m_transMatrix;
	CMatrix				m_scaleMatrix;
	CQuaternion			m_rotation;
};

