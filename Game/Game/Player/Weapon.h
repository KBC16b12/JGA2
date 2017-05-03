#pragma once

class Bullet;
class Player;
#define BULLET_NUM 100
#define STRIKE_NUM 30

class Weapon : public IGameObject
{
public:
	enum BULLETSTATE
	{
		BULLETSTATE_NOMAL,
		BULLETSTATE_GRENADE,
		BULLETSTATE_BOUND,
		BULLETSTATE_NUM,
	};
	Weapon();

	~Weapon();

	/*
	*@brief �������֐�
	*/
	void Init(Player* player, int playerNum);

	bool Start();

	/*
	*@brief �X�V����
	*/
	void Update();

	/*
	*@brief �e��ł��o���֐�
	*/
	void BulletFilling();

	/*
	*@brieg�@�A�C�e�����Ƃ����Ƃ��ɍX�V����֐�
	*/
	void SetWeapon();

	void OnDestroy()override;

	/*
	*@brief bullet�������֐�
	*@brief bullet���ŌĂяo��
	*@brief arraynum ��������bullet�̗v�f��
	*/
	void Delete(int arraynum)
	{
		if (m_bullet[arraynum] != nullptr)
		{
			DeleteGO((IGameObject*)m_bullet[arraynum]);
			m_bullet[arraynum] = nullptr;
		}
	}

	void ParticleEmit(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition);

	/*
	*@brief �`��֐�
	*@brief playernum �ǂ̃v���C���[�̎��_�ŕ`�悵������
	*/
	void Render(CRenderContext& renderContext, int playernum);

private:
	BULLETSTATE m_state;			//�ǂ̃A�C�e�����g���Ă邩�̏�Ԃ�\���ϐ�(NOMAL�͂Ȃ����)
	Player* m_player;				//�Q�Ɨp�̃v���C���[�̃C���X�^���X
	Bullet* m_bullet[BULLET_NUM];	//�e���Ǘ����Ă�z��
	int		m_bulletStrikeNum;		//�A�C�e�����g������Ԃ̒e��łĂ��
	int		m_playerNum;			
};