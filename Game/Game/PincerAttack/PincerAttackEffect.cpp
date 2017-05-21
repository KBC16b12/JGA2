#include "stdafx.h"
#include "PincerAttackEffect.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"


PincerAttackEffect::PincerAttackEffect()
{
	m_dot = 0.0f;
}


PincerAttackEffect::~PincerAttackEffect()
{
}


bool PincerAttackEffect::Start()
{
	m_pEffect = tkEngine::CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
	int color = 0xff0000ff;
	int color2 = 0x000000ff;
	CVector3 l_distance = g_gameScene->GetPlayer(m_opponentNum)->GetPosition();
	l_distance.Subtract(g_gameScene->GetPlayer(m_playerNum)->GetPosition());
	l_distance.y = 0.0f;
	float vertexZ = 0.5f;
	float vertexY = 0.7f;
	float vertexX = 0.2f;
	SShapeVertex_PC vertex[] =
	{
		{-vertexX, vertexY, vertexZ, 1.0f, color2},
		{ vertexX, vertexY, vertexZ, 1.0f, color},
		{ vertexX, -vertexY,-vertexZ, 1.0f, color},
		{ vertexX, -vertexY,-vertexZ, 1.0f, color },
		{-vertexX, -vertexY, -vertexZ, 1.0f, color2},
		{ -vertexX, vertexY, vertexZ, 1.0f, color2 },
	};
	int index[] = { 0, 1, 2, 3, 4, 5,};
	m_primitive.Create(
		CPrimitive::eTriangleList,
		sizeof(vertex) / sizeof(vertex[0]),
		sizeof(vertex[0]),
		scShapeVertex_PC_Element,
		vertex,
		sizeof(index) / sizeof(index[0]),
		eIndexFormat32,
		index
	);
	m_light.SetAmbinetLight(CVector3::One);
	return true;
}

void PincerAttackEffect::Update()
{
	m_worldMatrix = CMatrix::Identity;
	CVector3 l_trans = g_gameScene->GetPlayer(m_playerNum)->GetPosition();
	l_trans.Add(g_gameScene->GetPlayer(m_opponentNum)->GetPosition());
	l_trans.Div(2.0f);
	m_transMatrix.MakeTranslation(l_trans);
	CVector3 l_distance = g_gameScene->GetPlayer(m_opponentNum)->GetPosition();
	l_distance.Subtract(g_gameScene->GetPlayer(m_playerNum)->GetPosition());
	l_distance.y = 0.0f;
	CVector3 l_direction = l_distance;
	l_direction.Normalize();

	CVector3 l_scale = { 1.0f, 1.0f, l_distance.Length()};
	m_scaleMatrix.MakeScaling(l_scale);
	float l_dot = l_direction.Dot(CVector3::AxisZ);
	float angle = acos(l_dot);
	if (l_distance.x < 0.0f)
	{
		angle *= -1.0f;
	}
	m_rotationMatrix.MakeRotationY(angle);
	m_worldMatrix.Mul(m_worldMatrix, m_scaleMatrix);
	m_worldMatrix.Mul(m_worldMatrix, m_rotationMatrix);
	m_worldMatrix.Mul(m_worldMatrix, m_transMatrix);
}

void PincerAttackEffect::Render(CRenderContext& renderContext)
{
	CMatrix l_wvp;
	CMatrix l_vpm = g_gameCamera[0]->GetCamera().GetViewProjectionMatrix();
	l_wvp.Mul(m_worldMatrix, l_vpm);
	Draw(renderContext, l_wvp);
}

void PincerAttackEffect::Render(CRenderContext& renderContext, int playerNum)
{
	if (m_playerNum != playerNum)
	{
		return;
	}
	CMatrix l_wvp;
	CMatrix l_vpm = g_gameCamera[playerNum]->GetCamera().GetViewProjectionMatrix();
	l_wvp.Mul(m_worldMatrix, l_vpm);
	Draw(renderContext, l_wvp);
}

void PincerAttackEffect::Draw(CRenderContext& renderContext, CMatrix l_wvp)
{
	m_pEffect->SetTechnique(renderContext, "PincerEffect");
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);
	m_pEffect->SetValue(renderContext, "g_Dot", &m_dot, sizeof(m_dot));
	m_pEffect->SetValue(renderContext, "g_mWVP", &l_wvp, sizeof(l_wvp));
	m_pEffect->SetValue(renderContext, "g_worldRotationMatrix", &m_rotationMatrix, sizeof(m_rotationMatrix));
	m_pEffect->SetValue(
		renderContext,
		"g_light",
		&m_light,
		sizeof(CLight)
	);
	m_pEffect->CommitChanges(renderContext);
	renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
	renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);
	renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	renderContext.SetVertexDeclaration(m_primitive.GetVertexDecl());
	renderContext.SetStreamSource(0, m_primitive.GetVertexBuffer());
	renderContext.SetIndices(m_primitive.GetIndexBuffer());
	renderContext.DrawIndexedPrimitive(&m_primitive);
	renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}