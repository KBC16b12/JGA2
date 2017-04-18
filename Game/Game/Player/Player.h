#pragma once

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

	/*
	プレイヤーの番号をセットする関数
	プレイヤーの番号とカメラの番号は同じ
	*/
	void SetPlayerNum(int playernum)
	{
		m_playernum = playernum;
	}

	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext, int cameranum)override;

	void Move();

private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModel;					//スキンモデル
	CSkinModelData			m_skinModelData;				//スキンモデルデータ
	CQuaternion				m_rotation;					//回転
	CAnimation				m_Animation;					//アニメーション
	CCharacterController	m_characterController;		//キャラクタ―コントローラー。
	CVector3				m_position = { 0.0f, 40.0f, 0.0f };

	int						m_currentAnimationNo;
	float					m_angle = 180;

	Bar*			m_HPbar;		//HPバー
	int				m_hp;			//HP
	int				m_maxhp;		//最大HP
	int				m_playernum;
};

