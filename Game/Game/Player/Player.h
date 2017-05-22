#pragma once

#include "../Network/Network.h"
#include "Weapon.h"
class KillCountSprite;
class Bar;

class Player : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	Player();

	/*!
	*@brief	デストラクタ。
	*/
	~Player();

	/*!
	*@brief	開始関数。
	*@details
	* 初期化などをこの関数に実装してください。</br>
	* この関数がtrueを返すと本館数は以降のフレームでは呼ばれなくなります。</br>
	* そしてゲームオブジェクトの状態が初期化完了になりUpdate関数が呼ばれるようになります。</br>
	*@return	trueが帰ってきたら初期化完了。
	*/
	bool Start() override;

	/*!
	*@brief	更新関数。
	*/
	void Update() override;

	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext, int cameranum)override;

	void Render(CRenderContext& renderContext)override;

	void Move();

	/*
	*@brief ダメージを受けた時に呼ばれる関数
	*@brief int playerNum	当てたプレイヤーの番号
	*@brief int damage		プレイヤーが受けるダメージ量
	*/
	void Damage(int playerNum, int damage);

	/*
	*@brief リスポーン処理
	*/
	void Respawn();

	CVector3 GetPosition()
	{
		return m_position;
	}

	/*
	*@brief プレイヤーの前方のワールド行列
	*/
	CVector3 GetFrontWorldMatrix()
	{
		CVector3 l_frontWorldMatrix;
		CMatrix l_worldMatrix = m_skinModelFirst.GetWorldMatrix();
		l_frontWorldMatrix.x = l_worldMatrix.m[2][0];
		l_frontWorldMatrix.y = l_worldMatrix.m[2][1];
		l_frontWorldMatrix.z = l_worldMatrix.m[2][2];
		l_frontWorldMatrix.Scale(-1.0f);
		return l_frontWorldMatrix;
	}

	/*
	*@brief プレイヤー持ってる武器クラスにアイテムをセットする関数
	*/
	void SetWeapon()
	{
		m_weapon.SetWeapon();
	}

	void Init(CVector3 position, CQuaternion rotation)
	{
		m_rotation = rotation;
		m_position = position;
		m_respawnPosition = position;
		m_respawnRotation = rotation;
		CQuaternion multi;
		multi.SetRotation(CVector3::AxisX, CMath::DegToRad(90));
		m_rotation.Multiply(multi);
		multi.SetRotation(CVector3::AxisY, CMath::DegToRad(180));
		m_rotation.Multiply(multi);
	}

	/*
	プレイヤーの番号をセットする関数
	プレイヤーの番号とカメラの番号は同じ
	*/
	void SetPlayerNum(int playernum)
	{
		m_playernum = playernum;
		m_weapon.Init(m_playernum);
	}

	int GetPlayerNum()
	{
		return m_playernum;
	}
	
	void KillCountUp()
	{
		m_killCount++;
	}

	CMatrix GetWorldMatrix()
	{
		return m_skinModelFirst.GetWorldMatrix();
	}

private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModelFirst;					//自分から見た時のモデル
	CSkinModelDataHandle	m_skinModelDataFirst;				//スキンモデルデータ
	CSkinModel				m_skinModelThird;					//他人から見た時のモデル
	CSkinModelDataHandle	m_skinModelDataThird;
	CQuaternion				m_rotation;					//回転
	CAnimation				m_Animation;					//アニメーション
	CCharacterController	m_characterController;		//キャラクタ―コントローラー。
	CVector3				m_position = { 0.0f, 0.0f, 0.0f };
	CVector3				m_respawnPosition;					
	CQuaternion				m_respawnRotation;

	int						m_currentAnimationNo;

	KillCountSprite*		m_killCountSprite;					//キル数のスプライト
	Bar*					m_HPbar;		//HPバー
	int						m_hp;			//HP
	int						m_maxhp;		//最大HP
	int						m_playernum;
	int						m_killCount;
	Weapon					m_weapon;
	CLight					m_light;
};

