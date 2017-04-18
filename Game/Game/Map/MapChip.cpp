#include "stdafx.h"
#include "MapChip.h"
#include "../Camera/GameCamera.h"

MapChip::MapChip()
{
	//初期化
	m_position = CVector3::Zero;
	m_rotation = CQuaternion::Identity;
	m_scale = CVector3::Zero;
}

MapChip::~MapChip()
{
}

void MapChip::Init(SMapInfo map_dat)
{
	//スキンモデルロード
	char modelPath[1024];
	sprintf(modelPath, "Assets/modelData/%s.x", map_dat.s_modelName);
	SkinModelDataResources().Load(m_SkinModelData, modelPath, NULL, false, 1);
	m_SkinModel.Init(m_SkinModelData.GetBody());
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);
	//基本情報設定
	m_position = map_dat.s_position;
	m_rotation = map_dat.s_rotation;
	m_scale = map_dat.s_scale;
	m_SkinModel.Update(m_position, m_rotation, m_scale);


}

bool MapChip::Start()
{
	return true;
}

void MapChip::Update()
{
}

void MapChip::Render(CRenderContext& renderContext, int cameranum)
{
	m_SkinModel.Draw(renderContext, g_gameCamera[cameranum]->GetViewMatrix(), g_gameCamera[cameranum]->GetProjectionMatrix());
}