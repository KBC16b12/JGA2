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
		BULLETSTATE_NUM
	};
	Weapon();

	~Weapon();

	/*
	*@brief 初期化関数
	*/
	void Init(Player* player);

	bool Start();

	/*
	*@brief 更新処理
	*/
	void Update();

	/*
	*@brief 弾を打ち出す関数
	*/
	void BulletFilling();

	/*
	*@brieg　アイテムをとったときに更新する関数
	*/
	void SetWeapon();

	/*
	*@brief bulletを消す関数
	*@brief bullet側で呼び出す
	*@brief arraynum 消したいbulletの要素数
	*/
	void Delete(int arraynum)
	{
		DeleteGO((IGameObject*)m_bullet[arraynum]);
		m_bullet[arraynum] = nullptr;
	}

	/*
	*@brief 描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	void Render(CRenderContext& renderContext, int playernum);

private:
	BULLETSTATE m_state;			//どのアイテムを使ってるかの状態を表す変数(NOMALはない状態)
	Player* m_player;				//参照用のプレイヤーのインスタンス
	Bullet* m_bullet[BULLET_NUM];	//弾を管理してる配列
	int		m_bulletStrikeNum;		//アイテムを使った状態の弾を打てる回数
};