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
	enTecShaderHandle_Invincible,										//!<Toon用テクニック
	enTecShaderHandle_Num,
};