
#ifndef _CVIEWPORTSPRIT_H_
#define _CVIEWPORTSPRIT_H_

/*
画面分割するクラス(作オスマル)
*/


namespace tkEngine
{
	/*
	*@param x		左上の隅のx座標
	*@param y		左上の隅のy座標
	*@param width	xからの横幅
	*@param height	yからの縦幅
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

		//描画関数
		void Render(CRenderContext& renderContext, std::vector<GameObjectList>& objectList);

		void PostRender(CRenderContext& renderContext, std::vector<GameObjectList>& objectList);

		/*
		*@brief 画面分割する際の左上の隅の座標とそこからの幅
		*@param x		左上の隅のx座標
		*@param y		左上の隅のy座標
		*@param width	xからの横幅
		*@param height	yからの縦幅
		*/
		void SetSprit(ViewPortParam param)
		{
			m_viewPortParam.push_back(param);
		}

		ViewPortParam GetSprit(int playerNum)
		{
			return m_viewPortParam[playerNum];
		}

		void SetCameraNum(int cameraNum)
		{
			m_cameraNum = cameraNum;
		}

		//画面分割開始
		void Start()
		{
			m_isSprit = true;
		}

		//画面分割終了
		void Finish()
		{
			m_isSprit = false;
			Release();
		}

		//画面分割の情報を開放
		void Release();

	private:
		int	m_cameraNum;
		bool m_isSprit;									//画面分割するか
		std::vector<ViewPortParam> m_viewPortParam;		//画面分割する際の情報
	};
}
#endif // _CVIEWPORTSPRIT_H_