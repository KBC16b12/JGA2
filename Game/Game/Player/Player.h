#pragma once

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

	void PostRender(CRenderContext& renderContext, int cameranum)override;

	void Move();



	/*
	*@brief ダメージを受けた時に呼ばれる関数
	*@brief int playerNum
	*/
	void Damage(int playerNum);

	void Trap();

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
		CMatrix l_worldMatrix = m_skinModel.GetWorldMatrix();
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

	/*
	プレイヤーの番号をセットする関数
	プレイヤーの番号とカメラの番号は同じ
	*/
	void SetPlayerNum(int playernum)
	{
		m_playernum = playernum;
		m_weapon.Init(this, m_playernum);
	}

	int GetPlayerNUm()
	{
		return m_playernum;
	}
	
	void KillCountUp()
	{
		m_killCount++;
	}

	void Startup();

	bool IsStup()
	{
		return Stup;
	}
private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModel;					//スキンモデル
	CSkinModelData			m_skinModelData;				//スキンモデルデータ
	CQuaternion				m_rotation;						//回転
	CAnimation				m_Animation;					//アニメーション
	CCharacterController	m_characterController;		//キャラクタ―コントローラー。
	CVector3				m_position = { 0.0f, 40.0f, 0.0f };
	CVector3				m_respawnPosition;
	CQuaternion				m_respawnRotation;

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
	int						m_time = 75;
	int						Ctime = 100;
	Weapon					m_weapon;
};

