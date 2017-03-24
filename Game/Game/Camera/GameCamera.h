#pragma once
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


private:
	CCamera					m_camera;				//カメラ
	CCharacterController	m_characterController;	//キャラクタ―コントローラー
	CVector3				m_position;				//座標
	CVector3				m_look_position;		//注視点
	
	float					m_angle;				//角度
};

extern GameCamera* g_gameCamera;