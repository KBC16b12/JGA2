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

	virtual ~Item();
	/*
	*@brief 初期化関数
	*/
	virtual void Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModelData, CAnimation* animation);

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

	virtual void PostRender(CRenderContext& renderContext, int playernum)override;

	virtual void PostRender(CRenderContext& renderContext)override;

	bool IsDeath()
	{
		return m_isDeath;
	}
protected:

	virtual void Death(Player *player);

	void SetSpritePosition();

protected:
	const CVector2				m_size = {500.0f, 500.0f};
	CVector2					m_screenPos[PLAYER_NUM];
	CVector2					m_spriteSize[PLAYER_NUM];
	CTexture*					m_texture;
	CSprite						m_sprite;
	//CMeshCollider				m_meshCollider;		//メッシュコライダー。
	//CRigidBody					m_rigidBody;		//剛体。
	CSkinModel					m_SkinModel;		//スキンモデル4
	CAnimation*					m_animation;
	CVector3					m_position;			//座標
	CQuaternion					m_rotation;			//回転
	bool						m_isDeath;
	bool						m_isSpriteRender;
	bool m_isOpen;
};
