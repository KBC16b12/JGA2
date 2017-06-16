
#ifndef _CVIEWPORTSPRIT_H_
#define _CVIEWPORTSPRIT_H_

/*
��ʕ�������N���X(��I�X�}��)
*/


namespace tkEngine
{
	/*
	*@param x		����̋���x���W
	*@param y		����̋���y���W
	*@param width	x����̉���
	*@param height	y����̏c��
	*/
	struct ViewPortParam
	{
		int x;		
		int y;			
		int width;		
		int height;		
	};
	class CViewPortSprit
	{
	private:
		typedef std::list<IGameObject*> GameObjectList;

	public:
		CViewPortSprit();

		~CViewPortSprit();

		//�`��֐�
		void Render(CRenderContext& renderContext, std::vector<GameObjectList>& objectList);

		void PostRender(CRenderContext& renderContext, std::vector<GameObjectList>& objectList);

		/*
		*@brief ��ʕ�������ۂ̍���̋��̍��W�Ƃ�������̕�
		*@param x		����̋���x���W
		*@param y		����̋���y���W
		*@param width	x����̉���
		*@param height	y����̏c��
		*/
		void SetSprit(ViewPortParam param)
		{
			m_viewPortParam.push_back(param);
		}

		void SetCameraNum(int cameraNum)
		{
			m_cameraNum = cameraNum;
		}

		//��ʕ����J�n
		void Start()
		{
			m_isSprit = true;
		}

		//��ʕ����I��
		void Finish()
		{
			m_isSprit = false;
			Release();
		}

		//��ʕ����̏����J��
		void Release();

	private:
		int	m_cameraNum;
		bool m_isSprit;									//��ʕ������邩
		std::vector<ViewPortParam> m_viewPortParam;		//��ʕ�������ۂ̏��
	};
}
#endif // _CVIEWPORTSPRIT_H_