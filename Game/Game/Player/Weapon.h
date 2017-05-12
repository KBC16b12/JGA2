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
	*@brief 初期化関数
	*/
	void Init(Player* player, int playerNum);

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


private:
	BULLETSTATE m_state;				//どのアイテムを使ってるかの状態を表す変数(NOMALはない状態)
	Player*		m_player;				//参照用のプレイヤーのインスタンス
	int			m_bulletStrikeNum;		//アイテムを使った状態の弾を打てる回数
	int			m_playerNum;			
	ItemSprite	*m_itemSprite;
};