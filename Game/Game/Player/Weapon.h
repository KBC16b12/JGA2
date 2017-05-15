#pragma once

class ItemSprite;
class Bullet;
class Player;
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

	bool Start()override;

	/*
	*@brief �X�V����
	*/
	void Update()override;

	/*
	*@brief �e��ł��o���֐�
	*/
	void BulletFilling();

	/*
	*@brieg�@�A�C�e�����Ƃ����Ƃ��ɍX�V����֐�
	*/
	void SetWeapon();


private:
	BULLETSTATE m_state;				//�ǂ̃A�C�e�����g���Ă邩�̏�Ԃ�\���ϐ�(NOMAL�͂Ȃ����)
	Player*		m_player;				//�Q�Ɨp�̃v���C���[�̃C���X�^���X
	int			m_bulletStrikeNum;		//�A�C�e�����g������Ԃ̒e��łĂ��
	int			m_playerNum;			
	ItemSprite*	m_itemSprite;
	float		m_strikeInterval;		//�e��ł��Ă��玟�̒e��ł܂ł̃C���^�[�o��
	bool		m_isStrike;				//�e��łĂ邩�ǂ���

};
