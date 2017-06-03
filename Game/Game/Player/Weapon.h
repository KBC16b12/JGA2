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
	*@brief 初期化関数
	*/
	void Init(int playerNum);

	bool Start()override;

	/*
	*@brief 更新処理
	*/
	void Update()override;

	/*
	*@brief 弾を打ち出す関数
	*/
	void BulletFilling();

	/*
	*@brieg　アイテムをとったときに更新する関数
	*/
	void SetWeapon();

	void Reload();
private:
	BULLETSTATE m_state;				//どのアイテムを使ってるかの状態を表す変数(NOMALはない状態)
	int			m_bulletStrikeNum;		//アイテムを使った状態の弾を打てる回数
	int			m_playerNum;			
	ItemSprite*	m_itemSprite;
	MagazineSprite* m_magazineSprite;
	float		m_strikeInterval;		//弾を打ってから次の弾を打つまでのインターバル
	bool		m_isStrike;				//弾を打てるかどうか
	PincerAttack* m_pincer;
	float		m_reloadTime;
	bool		m_isReload;
	int			m_magazine;

};
