#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/ViewPortSprit/tkViewPortSprit.h"


namespace tkEngine
{
	CViewPortSprit::CViewPortSprit()
	{
		m_isSprit = false;
		m_cameraNum = 0;
	}

	CViewPortSprit::~CViewPortSprit()
	{
	}

	void CViewPortSprit::Render(CRenderContext& renderContext, std::vector<GameObjectList>& objectList)
	{
		if (m_isSprit)
		{
			int cameraNum = 0;
			//‰æ–Ê•ªŠ„‚µ‚Ä‚¢‚½ê‡ƒJƒƒ‰‚Ì”‚¾‚¯‚à‚¤ˆê‰ñ•`‰æ‚·‚é
			for (ViewPortParam camera : m_viewPortParam)
			{
				renderContext.SetViewport({(DWORD)camera.x, (DWORD)camera.y, (DWORD)camera.width, (DWORD)camera.height, 0.0f, 1.0f});
				for (GameObjectList objList : objectList) {
					for (IGameObject* obj : objList) {
						obj->RenderWrapper(renderContext, cameraNum);
					}
				}
				cameraNum++;
			}
		}
		else
		{
			//‰æ–Ê•ªŠ„‚µ‚Ä‚¢‚È‚¢ê‡•’Ê‚É•`‰æ‚·‚é
			for (GameObjectList objList : objectList) {
				for (IGameObject* obj : objList) {
					obj->RenderWrapper(renderContext, m_cameraNum);
				}
			}
		}
	}

	void CViewPortSprit::PostRender(CRenderContext& renderContext, std::vector<GameObjectList>& objectList)
	{
		if (m_isSprit)
		{
			//‰æ–Ê•ªŠ„‚µ‚Ä‚¢‚½ê‡ƒJƒƒ‰‚Ì”‚¾‚¯‚à‚¤ˆê‰ñ•`‰æ‚·‚é
			int cameraNum = 0;
			for (ViewPortParam camera : m_viewPortParam)
			{
				renderContext.SetViewport({ (DWORD)camera.x, (DWORD)camera.y, (DWORD)camera.width, (DWORD)camera.height, 0.0f, 1.0f });
				for (GameObjectList objList : objectList) {
					for (IGameObject* obj : objList) {
						obj->PostRenderWrapper(renderContext, cameraNum);
					}
				}
				cameraNum++;
			}
		}
		else
		{
			for (GameObjectList objList : objectList) {
				for (IGameObject* obj : objList) {
					obj->PostRenderWrapper(renderContext);
				}
			}
		}
	}

	void CViewPortSprit::Release()
	{
		while (!m_viewPortParam.empty())
		{
			m_viewPortParam.pop_back();
		}
	}

}