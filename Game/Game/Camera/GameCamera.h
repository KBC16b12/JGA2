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

	void Move();
	/*
	*@brief 描画関数
	ここでカメラ毎のオブジェクトを描画する
	*/
	void Render(CRenderContext&)override;

	void PostRender(CRenderContext&)override;

	/*
	*@brief ビューポートの矩形の場所とカメラの番号付けする関数
	x		左上隅のx座標
	y		左上隅のy座標
	width	xからの横幅
	height	yからの縦幅
	cameranum カメラの番号
	*/
	void SetViewPort(int x, int y, int width, int height, int cameranum);


	/*
	*@brief 画面分割が終わったら呼ぶ関数
	*/
	void FinishViewPort()
	{
		m_ViewportFlg = false;
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
private:
	CCamera					m_camera;				//カメラ
	CVector3				m_position;				//座標
	CVector3				m_look_position;		//注視点
	SViewport				m_sviewPort;
	float					m_angle;				//角度
	int						m_playernum;			//ビューポートで区切ったときのカメラの番号
	bool					m_ViewportFlg;
	Player*					m_player;
};

extern GameCamera* g_gameCamera[PLAYER_NUM];