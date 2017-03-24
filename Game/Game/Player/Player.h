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

	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext);
private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();

	Bar*			m_HPbar;		//HPバー
	int				m_hp;			//HP
	int				m_maxhp;		//最大HP
};

