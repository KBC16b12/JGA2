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
			//��ʕ������Ă����ꍇ�J�����̐������������`�悷��
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
			//��ʕ������Ă��Ȃ��ꍇ���ʂɕ`�悷��
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
			//��ʕ������Ă����ꍇ�J�����̐������������`�悷��
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
					obj->PostRenderWrapper(renderContext, m_cameraNum);
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