#pragma once

class Bar : public IGameObject
{
public:
	/*!
	*@brief	どちらに減っていくか。
	*/
	enum enBarQuarter
	{
		enQuaUp,
		enQuaDown,
		enQuaLeft,
		enQuaRight,
		enQuaNum,
	};

	enum EnState {
		enState_Normal,
		enState_DamageWait,		//ダメージ演出開始の待ち。
		enState_Damage,			//ダメージ演出。
	};

	/*!
	*@brief これで補正をかける。
	*/
	struct Correction
	{
		CVector2 pos;
		CVector2 pivot;
	};

	/*!
	*@brief	コンストラクタ。
	*/
	Bar();

	/*!
	*@brief	デストラクタ。
	*/
	~Bar();

	/*!
	*@brief	更新関数。
	*/
	void Update();

	/*!
	*@brief	描画関数。
	*/
	void PostRender(CRenderContext& renderContext);

	/*!
	*@brief	どの向きに減るかを設定。
	*/
	void SetBerQuarter(enBarQuarter qua)
	{
		m_Quarter = qua;
	}

	/*!
	*@brief	バーのファイルパス設定。
	*/
	void SetBarPath(char* path, unsigned int color = 0)
	{
		if (strcmp(m_BarPath, path) != 0)
		{
			m_BarPath = path;
			m_BarTex = TextureResources().LoadEx(m_BarPath, color);
			m_Bar.SetTexture(m_BarTex);
		}
	}

	/*!
	*@brief	ダメージバーのファイルパス設定。
	*/
	void SetBarBackPath(char* path, unsigned int color = 0)
	{
		if (strcmp(m_BarBackPath, path) != 0)
		{
			m_BarBackPath = path;
			m_BarBackTex = TextureResources().LoadEx(m_BarBackPath, color);
			m_BarBack.SetTexture(m_BarBackTex);
		}
	}

	/*!
	*@brief	背景のファイルパス設定。
	*/
	void SetGaugePath(char* path, unsigned int color = 0)
	{
		if (strcmp(m_GaugePath, path) != 0)
		{
			m_GaugePath = path;
			m_GaugeTex = TextureResources().LoadEx(m_GaugePath, color);
			m_Gauge.SetTexture(m_GaugeTex);
		}
	}

	/*!
	*@brief	バーのデータ設定(実質この処理で更新)。
	*/
	void SetData(int data, int max_data)
	{
		m_data = data;
		m_max_data = max_data;
	}

	/*!
	*@brief	バーの座標設定。
	*		この座標はピボットに依存せず、「左中央」の座標にしてください。
	*/
	void SetBarPos(CVector2 pos)
	{
		m_BarPos = pos;
		m_Bar.SetPosition(pos);
		m_BarBack.SetPosition(pos);
	}

	/*!
	*@brief	バーの最大サイズ設定。
	*/
	void SetBarMaxSize(CVector2 size)
	{
		m_BarMaxSize = size;
		m_Bar.SetSize(size);
		m_BarBack.SetSize(size);
	}

	/*!
	*@brief	背景の座標設定。
	*/
	void SetGaugePos(CVector2 pos)
	{
		m_Gauge.SetPosition(pos);
	}

	/*!
	*@brief	背景の最大サイズ設定。
	*/
	void SetGaugeMaxSize(CVector2 size)
	{
		m_Gauge.SetSize(size);
	}

private:
	/*!
	*@brief	バーの更新関数。
	*/
	void Bar_Update();

	/*!
	*@brief ピボットを設定。
	*/
	void Bar_Pivot();

	/*!
	*@brief 座標を設定。
	*/
	void Bar_Pos();

	/*!
	*@brief	m_stateがenState_Damageのときに呼ぶ。
	*/
	void Bar_Damage();

	/*!
	*@brief	m_stateがenState_Normalのときに呼ぶ。
	*/
	void Bar_Normal();

	/*!
	*@brief	m_stateがenState_DamageWaitのときに呼ぶ。
	*/
	void Bar_Wait();

	CSprite				m_Bar;			//バー。
	CTexture*			m_BarTex;		//バーのテクスチャ。
	char*				m_BarPath;		//バーのファイルパス。
	CVector2			m_BarPos;		//バーの座標
	
	CVector2			m_BarMaxSize;	//バーの最大座標
		
	CSprite				m_Gauge;		//ゲージ。
	CTexture*			m_GaugeTex;		//ゲージのテクスチャ。
	char*				m_GaugePath;	//ゲージのファイルパス。

	CSprite				m_BarBack;		//バーの背景。
	CTexture*			m_BarBackTex;	//バーの背景のテクスチャ
	char*				m_BarBackPath;	//バーの背景のファイルパス

	int					m_data;			//現在の値
	int					m_old_data;		//直前の値
	int					m_max_data;		//最大値

	float				m_timer;		//タイマー。

	EnState				m_state;		//ダメージ演出ステータス

	enBarQuarter		m_Quarter;		//どちらに減っていくか
};


