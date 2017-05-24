#pragma once
#include "Map/MapChip.h"

/*
マップにあるアイテムボックスのクラス
*/

class Player;

class Item : public IGameObject
{
public:
	Item();

	~Item();
	/*
	*@brief 初期化関数
	*/
	virtual void Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModelData);

	/*
	*@brief 更新関数
	*/
	virtual void Update()override;

	virtual bool Start()override;

	/*
	*@brief 描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	virtual void Render(CRenderContext& renderContext, int playernum)override;

	virtual void Render(CRenderContext& renderContext)override;

	bool IsDeth()
	{
		return m_isDeth;
	}
protected:
	virtual void Deth(Player *player);

private:
	CMeshCollider				m_meshCollider;			//メッシュコライダー。
	CRigidBody					m_rigidBody;			//剛体。
	CSkinModel					m_SkinModel;		//スキンモデル
	CVector3					m_position;			//座標
	CQuaternion					m_rotation;			//回転
	bool						m_isDeth;

};
