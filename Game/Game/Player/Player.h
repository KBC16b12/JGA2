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

	void Render(CRenderContext& renderContext)override;

	void PostRender(CRenderContext& renderContext, int cameranum)override;

	void Move();

	/*
	*@brief ダメージを受けた時に呼ばれる関数
	*@brief int playerNum
	*/
	void Damage(int playerNum);

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

	void SetPosition(CVector3 position)
	{
		m_position = position;
		m_respawnPosition = position;
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

	int GetPlayerNum()
	{
		return m_playernum;
	}

	bool IsLoadEnd()
	{
		return (m_skinModelDataFirst.IsLoadEnd() && m_skinModelDataThird.IsLoadEnd());
	}
	
	void KillCountUp()
	{
		m_killCount++;
	}

private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModelFirst;					//スキンモデル
	CSkinModelDataHandle	m_skinModelDataFirst;				//スキンモデルデータ
	CSkinModel				m_skinModelThird;
	CSkinModelDataHandle	m_skinModelDataThird;
	CQuaternion				m_rotation;					//回転
	CAnimation				m_Animation;					//アニメーション
	CCharacterController	m_characterController;		//キャラクタ―コントローラー。
	CVector3				m_position = { 0.0f, 0.0f, 0.0f };
	CVector3				m_respawnPosition;
	CQuaternion				m_respawnRotation;

	int						m_currentAnimationNo;
	float					m_angle = 180;

	KillCountSprite*		m_killCountSprite;					//キル数のスプライト
	Bar*					m_HPbar;		//HPバー
	int						m_hp;			//HP
	int						m_maxhp;		//最大HP
	int						m_playernum;
	int						m_killCount;
	Weapon					m_weapon;
	CLight					m_light;
};

