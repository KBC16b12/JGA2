#pragma once

class ItemSprite;
class MagazineSprite;
class Bullet;
class Player;
class PincerAttack;
#define STRIKE_NUM 30
#define MAGAZINE_SIZE 15

enum BULLETSTATE
{
	BULLETSTATE_NOMAL,
	BULLETSTATE_GRENADE,
	BULLETSTATE_BOUND,
	BULLETSTATE_NUM,
};
class Weapon : public IGameObject
{
public:

	Weapon();

	~Weapon();

	/*
	*@brief �������֐�
	*/
	void Init(int playerNum);

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

	void Reload();


private:
	BULLETSTATE m_state;				//�ǂ̃A�C�e�����g���Ă邩�̏�Ԃ�\���ϐ�(NOMAL�͂Ȃ����)
	int			m_bulletStrikeNum;		//�A�C�e�����g������Ԃ̒e��łĂ��
	int			m_playerNum;			
	ItemSprite*	m_itemSprite;
	MagazineSprite* m_magazineSprite;
	float		m_strikeInterval;		//�e��ł��Ă��玟�̒e��ł܂ł̃C���^�[�o��
	bool		m_isStrike;				//�e��łĂ邩�ǂ���
	PincerAttack* m_pincer;
	float		m_reloadTime;
	bool		m_isReload;
	int			m_magazine;

};
