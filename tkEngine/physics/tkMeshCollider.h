#pragma once
#include "tkEngine/Physics/tkICollider.h"

namespace tkEngine{

	/*!
	 * @brief	メッシュコライダー。
	 */
	class CMeshCollider : public ICollider
	{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CMeshCollider();
		/*!
		 * @brief	デストラクタ。
		 */
		~CMeshCollider();
		/*!
		 * @brief	CSkinModelからメッシュコライダーを生成。
		 *@param[in]	model		スキンモデル。
		 */
		void CreateFromSkinModel( CSkinModel* model, const CMatrix* offsetMatrix );
		btCollisionShape* GetBody() override
		{
			return meshShape;
		}
		const CVector3& GetAABBMax() const
		{
			return aabbMax;
		}
		const CVector3& GetAABBMin() const
		{
			return aabbMin;
		}
	private:
		typedef std::vector<CVector3>		VertexBuffer;		//頂点バッファ。
		typedef std::vector<unsigned int>	IndexBuffer;		//インデックスバッファ。
		std::vector<VertexBuffer*>		vertexBufferArray;		//頂点バッファの配列。
		std::vector<IndexBuffer*>		indexBufferArray;		//インデックスバッファの配列。
		btBvhTriangleMeshShape*			meshShape;				//メッシュ形状。
		btTriangleIndexVertexArray*		stridingMeshInterface;
		CVector3						aabbMax;
		CVector3						aabbMin;
	};
}
