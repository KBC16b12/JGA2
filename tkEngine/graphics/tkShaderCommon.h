#pragma once
/*!
*@brief	シェーダーテクニックのハンドル。
*/
enum EnShaderTechnique {
	enTecShaderHandle_SkinModelInstancingRenderToShadowMap,		//!<SkinModelInstancingRenderToShadowMapテクニック
	enTecShaderHandle_SkinModelInstancing,						//!<SkinModelInstancingテクニック。
	enTecShaderHandle_NoSkinModelInstancingRenderToShadowMap,	//!<NoSkinModelInstancingRenderToShadowMapテクニック。
	enTecShaderHandle_NoSkinModelInstancing,					//NoSkinModelInstancingテクニック。
	enTecShaderHandle_SkinModelRenderShadowMap,					//!<SkinModelRenderShadowMapテクニック。
	enTecShaderHandle_SkinModel,								//!<SkinModelテクニック。
	enTecShaderHandle_NoSkinModelRenderShadowMap,				//!<NoSkinModelRenderShadowMapテクニック。
	enTecShaderHandle_NoSkinModel,								//!<NoSkinModelテクニック。
	enTecShaderHandle_Sky,										//!<Skyテクニック。
	enTecShaderHandle_Terrain,									//!<Terrain用テクニック。
	enTecShaderHandle_Invincible,										//!<プレイヤーが無敵状態の時のテクニック
	enTecShaderHandle_PincerBullet,
	enTecShaderHandle_Num,
};