#pragma once

#include "../Network/Network.h"
#include "Weapon.h"
#include "PlayerRecovery.h"
class KillCountSprite;
class Bar;


enum
{
	ANIMESTATE_WAIT,
	ANIMESTATE_SHOT,
	ANIMESTATE_RELOAD,
	ANIMESTATE_NUM,
};
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
	void Damage(int playerNum, int damage, CVector3 moveSpeed, CVector3 bulletPosition);

	void Trap();

	/*
	*@brief リスポーン処理
	*/
	void Respawn();

	CVector3 GetPosition()
	{
		return m_position;
	}

	CQuaternion GetRotation()
	{
		return m_rotation;
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

	void Init(CVector3 position, CQuaternion rotation, int playernum);

	void Death(CVector3 moveSpeed);


	int GetPlayerNum()
	{
		return m_playernum;
	}
	
	void KillCountUp();

	int GetKillCount()
	{
		return m_killCount;
	}

	void Startup();

	bool IsStup()
	{
		return Stup;
	}
	CMatrix GetWorldMatrix()
	{
		return m_skinModelFirst.GetWorldMatrix();
	}

	void Eaten();

	
	int GetMaxHP()
	{
		return m_maxhp;
	}

	void SetIsPincer(bool isPincerAttack)
	{
		m_weapon.SetIsPincer(isPincerAttack);
	}

	bool IsInvincible()
	{
		return m_isInvincible;
	}

	int GetHP()
	{
		return m_hp;
	}
private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();

	/*!
	*@brief	キー入力情報出力。
	*/
	void KeyOutput();

	/*!
	*@brief	生データ出力。
	*/
	void DataOutput();

	void Invincible();

private:
	CSkinModel				m_skinModelFirst;					//自分から見た時のモデル
	CSkinModelData			m_skinModelDataFirst;				//スキンモデルデータ
	CSkinModel				m_skinModelThird;					//他人から見た時のモデル
	CSkinModelData			m_skinModelDataThird;
	CQuaternion				m_rotation;					//回転
	CAnimation				m_Animation;					//アニメーション
	CCharacterController	m_characterController;		//キャラクタ―コントローラー。
	CVector3				m_position = { 0.0f, 0.0f, 0.0f };

	int						m_currentAnimationNo;
	float					m_angle = 180;
	float					move = -5.0f;	//移動速度
	bool					Stup = false;
	KillCountSprite*		m_killCountSprite;					//キル数のスプライト
	Bar*					m_HPbar;		//HPバー
	int						m_hp;			//HP
	int						m_maxhp;		//最大HP
	int						m_playernum;
	int						m_killCount;
	int						m_time = 30;
	int						Ctime = 15;
	bool					m_isInvincible;
	bool					m_isInvincibleTec;
	float					m_invincibleTecCount;	//テクニックを切り替える時間
	float					m_invincibleCount;		//リスキル防止の無敵時間を数える変数
	bool					m_isRendering;
	Weapon					m_weapon;
	CLight					m_light;
	PlayerRecovery*			m_recovery;
	CAnimation				m_animation;
	const int				m_height = 3.95f;
};

