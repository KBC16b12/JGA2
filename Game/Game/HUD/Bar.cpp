#include "stdafx.h"
#include "Bar.h"

Bar::Bar()
{
	//バーの初期化
	m_BarPath = "Assets/sprite/Black.png";
	m_BarTex = TextureResources().LoadEx(m_BarPath);
	m_Bar.Init(m_BarTex);
	m_Bar.SetPivot({ 0.0f, 0.5f });
	SetBarMaxSize(CVector2::Zero);
	SetBarPos(CVector2::Zero);

	//背景の初期化
	m_GaugePath = "Assets/sprite/Black.png";
	m_GaugeTex = TextureResources().LoadEx(m_GaugePath);
	m_Gauge.Init(m_GaugeTex);
	m_Gauge.SetPivot({ 0.0f, 0.5f });
	SetGaugeMaxSize(CVector2::Zero);
	SetGaugePos(CVector2::Zero);

	//ダメージ演出のバーの初期化
	m_BarBackPath = "Assets/sprite/Black.png";
	m_BarBackTex = TextureResources().LoadEx(m_BarBackPath);
	m_BarBack.Init(m_BarBackTex);
	m_BarBack.SetPivot({ 0.0f, 0.5f });


	m_data = 0;
	m_old_data = 0;
	m_max_data = 0;

	m_timer = 0.0f;

	m_state = enState_Normal;

	m_Quarter = enQuaLeft;

	m_BarPos = CVector2::Zero;
}

Bar::~Bar()
{
}

void Bar::Update()
{
	Bar_Update();
}

void Bar::Bar_Update()
{
	//最大データが0以下で早期リターン
	if (m_max_data <= 0)
	{
		return;
	}

	float Rate = (float)m_data / (float)m_max_data;
	CVector2 size = m_BarMaxSize;

	switch (m_Quarter)
	{
	case Bar::enQuaUp:
	case Bar::enQuaDown:
		size.y *= Rate;
		break;
	case Bar::enQuaLeft:
	case Bar::enQuaRight:
		size.x *= Rate;
		break;
	default:
		break;
	}
	m_Bar.SetSize(size);

	Bar_Pos();
	Bar_Pivot();

	switch (m_state) {
	case enState_Normal:
		Bar_Normal();
		break;
	case enState_DamageWait:
		Bar_Wait();
		break;
	case enState_Damage: {
		Bar_Damage();
	}break;
	}
	m_old_data = m_data;
}

void Bar::Bar_Pivot()
{
	//ピボット設定
	CVector2 pivot = CVector2::Zero;
	switch (m_Quarter)
	{
	case Bar::enQuaUp:
		pivot = { 0.0f,1.0f };
		break;
	case Bar::enQuaDown:
		pivot = { 0.0f,0.0f };
		break;
	case Bar::enQuaLeft:
		pivot = { 0.0f,0.5f };
		break;
	case Bar::enQuaRight:
		pivot = { 1.0f,0.5f };
		break;
	default:
		break;
	}
	m_Bar.SetPivot(pivot);
	m_BarBack.SetPivot(pivot);
}

void Bar::Bar_Pos()
{
	CVector2 pos = m_BarPos;

	//消えていく方向をもとに座標決定
	switch (m_Quarter)
	{
	case Bar::enQuaUp:
		pos.y += m_BarMaxSize.y / 2.0f;
		break;
	case Bar::enQuaDown:
		pos.y -= m_BarMaxSize.y / 2.0f;
		break;
	case Bar::enQuaLeft:
		break;
	case Bar::enQuaRight:
		pos.x += m_BarMaxSize.x;
		break;
	default:
		break;
	}
	m_Bar.SetPosition(pos);
	m_BarBack.SetPosition(pos);
}

void Bar::Bar_Normal()
{
	if (m_old_data > m_data) {
		//ダメージを受けた。
		m_state = enState_DamageWait;
		m_timer = 0.0f;
	}
	else if (m_old_data < m_data) {
		//回復している。
		m_BarBack.SetSize(m_Bar.GetSize());
	}
}

void Bar::Bar_Wait()
{
	m_timer += GameTime().GetFrameDeltaTime();
	if (m_timer > 0.5f) {
		//ダメージ演出開始。
		m_state = enState_Damage;
		m_timer = 0.0f;
	}
}

void Bar::Bar_Damage()
{
	//ダメージ処理
	CVector2 sizeBack = m_BarBack.GetSize();

	switch (m_Quarter)
	{
	case Bar::enQuaUp:
	case Bar::enQuaDown:
		sizeBack.y -= 20.f * GameTime().GetFrameDeltaTime();
		if (sizeBack.y < m_Bar.GetSize().y) {
			m_state = enState_Normal;
			sizeBack.y = m_Bar.GetSize().y;
		}
		break;
	case Bar::enQuaLeft:
	case Bar::enQuaRight:
		sizeBack.x -= 20.f * GameTime().GetFrameDeltaTime();
		if (sizeBack.x < m_Bar.GetSize().x) {
			m_state = enState_Normal;
			sizeBack.x = m_Bar.GetSize().x;
		}
		break;
	default:
		break;
	}
	m_BarBack.SetSize(sizeBack);
}

void Bar::PostRender(CRenderContext& renderContext)
{
	m_Gauge.Draw(renderContext);
	m_BarBack.Draw(renderContext);
	m_Bar.Draw(renderContext);
}
