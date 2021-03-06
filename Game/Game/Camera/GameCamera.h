#pragma once
class Player;

class GameCamera : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/

	GameCamera();

	/*!
	*@brief	デストラクタ。
	*/
	~GameCamera();

	/*!
	*@brief	更新関数。
	*/
	void Update();

	bool Start()override;

	/*
	*@brief 描画関数
	ここでカメラ毎のオブジェクトを描画する
	*/
	void Render(CRenderContext&)override;

	void PostRender(CRenderContext&)override;

	/*
	*@brief ビューポートを設定する関数
	x		左上隅のx座標
	y		左上隅のy座標
	width	xからの横幅
	height	yからの縦幅
	Player* カメラを持ってるプレイヤー
	*/
	void SetViewPort(ViewPortParam param, Player* player)
	{
		GetViewSprit().SetSprit(param);
		m_player = player;
		m_isViewport = true;
	}

	void FinishViewPort()
	{
		m_isViewport = false;
	}

	void SetPos();
	/*!
	*@brief	ビューマトリックスを返す。
	*/
	const CMatrix& GetViewMatrix() const
	{
		return m_camera.GetViewMatrix();
	}

	/*!
	*@brief	プロジェクションマトリックスを返す。
	*/
	const CMatrix& GetProjectionMatrix() const
	{
		return m_camera.GetProjectionMatrix();
	}

	int GetPlayerNum()
	{
		return m_playernum;
	}

	CCamera& GetCamera()
	{
		return m_camera;
	}

	void PlayAnime()
	{
		m_animation.PlayAnimation(0);
		m_isDead = true;
	}

	void Reset()
	{
		m_isDead = false;
	}

private:

	CCamera					m_camera;				//カメラ
	CVector3				m_position;				//座標
	CVector3				m_look_position;		//注視点

	SViewport				m_sviewPort;
	float					m_angle;				//角度
	int						m_playernum;			//ビューポートで区切ったときのカメラの番号
	bool					m_isViewport;
	Player*					m_player;
	CQuaternion				m_rotation;
	CSkinModel				m_skinModel;
	CSkinModelDataHandle	m_skinModelData;
	CAnimation				m_animation;
	CLight					m_light;
	bool					m_isDead;
	CMatrix*				m_worldMatrix;
};

extern GameCamera* g_gameCamera[PLAYER_NUM];