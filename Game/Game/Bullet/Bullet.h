#pragma once
#include "../Player/Weapon.h"

/*
弾の基底クラス
他のアイテムを使ったときに出る弾はこのクラスを継承させる
*/

class Bullet : public IGameObject
{
public:
	Bullet();

	~Bullet();

	bool Start()override;


	/*
	*@brief 弾の初期化処理
	*@brief moveSpeed		飛ぶ方向
	*@brief *weapon			自身を消す際に参照するウェポン
	*@brief arrayNum		自身を消す
	*/
	virtual void Init(CVector3 movespeed, Weapon *weapon, int arrayNum, int playerNum);


	/*
	*@brief 更新処理
	*/
	virtual void Update()override;


	/*
	*@brief 弾の動きの処理
	*/
	virtual void Move();

	virtual void DethCheck();
	/*
	*@brief 描画関数
	*/
	void Render(CRenderContext& renderContext)override;

	/*
	*@brief カメラ毎に呼ぶ描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	void Render(CRenderContext& renderContext, int playernum)override;

protected:
	CVector3				m_position;
	CVector3				m_moveSpeed;
	CSkinModel				m_skinModel;
	CSkinModelDataHandle	m_modelData;
	CLight					m_light;
	Weapon*					m_weapon;
	int						m_arraynum;
	int						m_playerNum;
};
