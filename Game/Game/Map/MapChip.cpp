#include "stdafx.h"
#include "MapChip.h"
#include "../Camera/GameCamera.h"

MapChip::MapChip()
{
	//初期化
	m_position = CVector3::Zero;
	m_rotation = CQuaternion::Identity;
}

MapChip::~MapChip()
{
}

void MapChip::ModelInit(const char *modelName)
{
	//スキンモデルロード
	char modelPath[1024];
	sprintf(modelPath, "Assets/modelData/%s.x", modelName);
	SkinModelDataResources().Load(m_SkinModelData, modelPath, NULL, false, 1);
	m_SkinModel.Init(m_SkinModelData.GetBody());
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);

}

void MapChip::Init(SMapInfo map_dat)
{
	ModelInit(map_dat.s_modelName);
	//基本情報設定
	m_position = map_dat.s_position;
	m_rotation = map_dat.s_rotation;
	CQuaternion l_rotation;
	l_rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(90));
	m_rotation.Multiply(l_rotation);
	m_SkinModel.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere);
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);
}

bool MapChip::Start()
{
	return true;
}

void MapChip::Update()
{
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);
}

void MapChip::Render(CRenderContext& renderContext, int cameranum)
{
	m_SkinModel.Draw(renderContext, g_gameCamera[cameranum]->GetViewMatrix(), g_gameCamera[cameranum]->GetProjectionMatrix());
}

void MapChip::Render(CRenderContext& renderContext)
{
	m_SkinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}