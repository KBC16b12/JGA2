/*!
 * @brief	テクスチャ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkTexture.h"

namespace tkEngine {
	/*!
	 * @brief	テクスチャをロード。
	 */
	bool CTexture::Load(const char* fileName, bool isCubeMap)
	{
		Release();
		LPDIRECT3DDEVICE9 device = Engine().GetD3DDevice();
		if (!isCubeMap) {
			if (FAILED(D3DXCreateTextureFromFile(
				device,
				fileName,
				&m_tex))) {
				TK_LOG("FailedTextureLoad\n");
				return false;
			}
		}
		else {
			if (FAILED(D3DXCreateCubeTextureFromFile(
				device,
				fileName,
				&m_cubeTex))) {
				TK_LOG("FailedTextureLoad\n");
				return false;
			}
		}
		ComputeTexSize();
		return true;
	}

	bool CTexture::LoadEx(const char* fileName, unsigned int color)
	{
		LPDIRECT3DDEVICE9 device = Engine().GetD3DDevice();
		if (FAILED(D3DXCreateTextureFromFileEx(
			device,
			fileName,
			0,
			0,
			0,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_FILTER_NONE,
			color,
			NULL,
			NULL,
			&m_tex))) {
			TK_LOG("FailedTextureLoad");
			return false;
		}
		ComputeTexSize();
		return true;
	}
}