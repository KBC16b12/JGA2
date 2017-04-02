#pragma once
/*!
* @brief	プリコンパイル済みヘッダー。
*/

#ifndef _STDAFX_H_
#define _STDAFX_H_

#pragma comment( lib, "WS2_32.LIB" )
#pragma warning ( disable : 4996 )

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/resource/tkSkinModelDataHandle.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"
#include "tkEngine/Physics/tkPhysics.h"
#include "tkEngine/physics/tkRigidBody.h"
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/character/tkCharacterController.h"


using namespace tkEngine;
#include "tkEngine/random/tkRandom.h"

#include "tkEngine/Sound/tkSoundSource.h"

#include "stuNamespace.h"
using namespace Status;

extern CRandom g_random;

extern CLight g_defaultLight;	//デフォルトライト。

#endif // _STDAFX_H_